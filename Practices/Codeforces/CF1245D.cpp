// CF1245D.cpp
#include <bits/stdc++.h>
#define ll long long
#define pr pair<int, int>

using namespace std;

const int MAX_N = 5050;

int n, xi[MAX_N], yi[MAX_N], ci[MAX_N], ki[MAX_N], mst[MAX_N];
ll min_cost[MAX_N], mat[MAX_N][MAX_N];
vector<pr> ans_vec;
set<int> construct;

void addpath(int src, int dst, ll weight) { mat[src][dst] = weight; }

ll mht(int x, int y) { return abs(xi[x] - xi[y]) + abs(yi[x] - yi[y]); }

int main()
{
    memset(mat, -1, sizeof(mat));
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &xi[i], &yi[i]);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ci[i]), addpath(0, i, ci[i]), addpath(i, 0, ci[i]);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ki[i]);
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            addpath(i, j, 1LL * (ki[i] + ki[j]) * mht(i, j)), addpath(j, i, 1LL * (ki[i] + ki[j]) * mht(i, j));
    ll ans = 0;
    for (int i = 1; i <= n; i++)
        if (mat[0][i] != -1)
            min_cost[i] = mat[0][i], mst[i] = 0;
    mst[0] = -1;
    for (int cnt = 1; cnt <= n; cnt++)
    {
        ll min_val = 0x3f3f3f3f3f3f3f3f;
        int pt = -1;
        for (int u = 1; u <= n; u++)
            if (mst[u] != -1 && min_cost[u] < min_val)
                min_val = min_cost[u], pt = u;
        if (pt == -1)
            continue;
        if (mst[pt] == 0)
            construct.insert(pt);
        else
            ans_vec.push_back(make_pair(mst[pt], pt));
        mst[pt] = -1, ans += min_cost[pt];
        for (int i = 1; i <= n; i++)
            if (min_cost[i] > mat[pt][i] && mst[i] != -1)
                min_cost[i] = mat[pt][i], mst[i] = pt;
    }
    printf("%lld\n", ans);
    printf("%lld\n", (ll)construct.size());
    for (set<int>::iterator it = construct.begin(); it != construct.end(); it++)
        printf("%d ", *it);
    puts("");
    printf("%lld\n", (ll)ans_vec.size());
    for (int i = 0, siz = ans_vec.size(); i < siz; i++)
        printf("%d %d\n", ans_vec[i].first, ans_vec[i].second);
    return 0;
}