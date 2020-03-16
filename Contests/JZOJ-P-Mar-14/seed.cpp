// seed.cpp
#pragma GCC optimize(2)
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

typedef long long ll;

int n, start_idx, stat_upper, bases[MAX_N];
double dp[(1 << 21)];

struct seed
{
    int pi;
    double vi, prob;
    bool operator<(const seed &rhs) const { return pi > rhs.pi; }
} seeds[MAX_N];

void fileIO()
{
    freopen("seed.in", "r", stdin);
    freopen("seed.out", "w", stdout);
}

inline double dfs(int stat)
{
    if (dp[stat] != -1)
        return dp[stat];
    double ret = 0;
    for (int i = 1; i <= n; i++)
    {
        int cnt = stat / bases[i] % (seeds[i].pi + 1);
        if (cnt == seeds[i].pi)
            ret += seeds[i].prob * seeds[i].vi;
        else
        {
            int nxtcode = stat + bases[i];
            ret += seeds[i].prob * max(dfs(nxtcode), seeds[i].vi);
        }
    }
    return dp[stat] = ret;
}

int main()
{
    // fileIO();
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%lf", &seeds[i].pi, &seeds[i].vi);
    sort(seeds + 1, seeds + 1 + n);
    for (start_idx = 1; seeds[start_idx].pi != 0; start_idx++)
        ;
    for (int i = 1; i <= n; i++)
        seeds[i].prob = 1.0 / n;
    if (start_idx <= n)
    {
        for (int i = start_idx + 1; i <= n; i++)
            seeds[start_idx].vi += seeds[i].vi;
        seeds[start_idx].vi /= (n - start_idx + 1);
        seeds[start_idx].prob = double(n - start_idx + 1) / n;
        seeds[start_idx].pi = 0, n = start_idx;
    }
    stat_upper = 1;
    for (int i = 1; i <= n; i++)
        bases[i] = stat_upper, stat_upper *= (seeds[i].pi + 1);
    for (int i = 0; i < stat_upper; i++)
        dp[i] = -1;
    double ans = dfs(0);
    printf("%.4lf\n", ans);
    return 0;
}