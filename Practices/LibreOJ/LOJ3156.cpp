// LOJ3156.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, MAX_M = 2e5 + 200;

typedef long long ll;

int n, m, A, B, C, xi[MAX_M], yi[MAX_M], pi[MAX_M], qi[MAX_N], deg[MAX_N];
ll dp[MAX_M], X[MAX_M], Y[MAX_M], ans = 1e18;
deque<int> q[MAX_N], inq[MAX_N], ouq[MAX_N];

double slope(int i, int j)
{
    if (X[i] == X[j])
        return Y[i] == Y[j] ? 0 : (Y[i] < Y[j] ? 1e99 : -1e99);
    return double(Y[i] - Y[j]) / double(X[i] - X[j]);
}

void fileIO()
{
    freopen("route.in", "r", stdin);
    freopen("route.out", "w", stdout);
}

int main()
{
    // fileIO();
    scanf("%d%d%d%d%d", &n, &m, &A, &B, &C);
    yi[0] = 1, ouq[0].push_back(0), deg[1]++;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d%d", &xi[i], &yi[i], &pi[i], &qi[i]);
        inq[pi[i]].push_back(i), ouq[qi[i]].push_back(i), deg[yi[i]]++;
    }
    for (int T = 0; T <= 1000; T++)
    {
        for (auto e : ouq[T])
        {
            // get the convex hull;
            int u = yi[e];
            while (q[u].size() >= 2 && slope(*(++q[u].rbegin()), *(q[u].rbegin())) > slope(*q[u].rbegin(), e))
                q[u].pop_back();
            q[u].push_back(e);
            if (yi[e] == n)
                ans = min(ans, dp[e] + qi[e]);
        }
        for (auto e : inq[T])
        {
            int u = xi[e];
            while (q[u].size() >= 2 && slope(*q[u].begin(), *(++q[u].begin())) < 2LL * A * T)
                q[u].pop_front();
            if (!q[u].empty())
                dp[e] = Y[q[u].front()] - 2LL * A * T * X[q[u].front()] + C + 1LL * A * T * T + 1LL * B * T;
            else
                dp[e] = 0x3f3f3f3f3f3f3f3f;
            X[e] = qi[e], Y[e] = 1LL * A * qi[e] * qi[e] - 1LL * B * qi[e] + dp[e];
        }
    }
    printf("%lld\n", ans);
    return 0;
}