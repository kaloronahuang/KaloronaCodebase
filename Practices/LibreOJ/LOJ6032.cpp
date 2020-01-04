// LOJ6032.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int n, m, height[MAX_N], h[MAX_N], mem[MAX_N], fa[20][MAX_N], ch[MAX_N][2], ptot, top[MAX_N];
int f[MAX_N][2], cnt0[MAX_N], T;
pair<int, int> pr[MAX_N];
vector<pair<int, bool> /**/> cond[MAX_N];

#define lson(s) ch[s][0]
#define rson(s) ch[s][1]

// dsu;

int find(int x) { return mem[x] == x ? x : mem[x] = find(mem[x]); }

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &n, &m), height[0] = 2e9;
        for (int i = 1; i < n; i++)
            scanf("%d", &h[i]), pr[i] = make_pair(h[i], i);
        sort(pr + 1, pr + n), ptot = n;
        // Dicale tree;
        for (int i = 1; i <= n; i++)
            fa[0][i] = ch[i][0] = ch[i][1] = 0, mem[i] = i, top[i] = i;
        for (int idx = 1; idx < n; idx++)
        {
            int u = find(pr[idx].second), v = find(pr[idx].second + 1);
            mem[v] = u, height[++ptot] = h[pr[idx].second];
            fa[0][ptot] = 0, fa[0][top[u]] = fa[0][top[v]] = ptot;
            ch[ptot][0] = top[u], ch[ptot][1] = top[v], top[u] = ptot;
        }
        for (int i = 1; i <= 19; i++)
            for (int j = 1; j <= ptot; j++)
                fa[i][j] = fa[i - 1][fa[i - 1][j]];
        for (int i = 1; i <= ptot; i++)
            cnt0[i] = 0, cond[i].clear();
        for (int i = 1, u, v, b; i <= m; i++)
        {
            scanf("%d%d%d", &u, &v, &b);
            int pt = u;
            for (int i = 19; i >= 0; i--)
                if (height[fa[i][pt]] <= v)
                    pt = fa[i][pt];
            cond[pt].push_back(make_pair(v, (bool)b));
            cnt0[pt] += !b;
        }
        for (int i = 1; i <= ptot; i++)
        {
            f[i][0] = f[i][1] = 0;
            if (!cond[i].empty())
            {
                sort(cond[i].begin(), cond[i].end());
                int presum = f[i][1] = cnt0[i] + (i > n ? f[ch[i][0]][0] + f[ch[i][1]][0] : 0);
                for (int l = 0, siz = cond[i].size(), r; l < siz; l = r + 1)
                {
                    r = l;
                    int acc = (cond[i][r].second ? 1 : -1);
                    while (r + 1 < siz && cond[i][r].first == cond[i][r + 1].first)
                        r++, acc += cond[i][r].second ? 1 : -1;
                    presum += acc, f[i][1] = max(f[i][1], presum);
                }
                f[i][0] = presum;
            }
            if (i > n)
                f[i][1] = max(f[i][1], cnt0[i] + f[ch[i][0]][1] + f[ch[i][1]][1]),
                f[i][0] = max(f[i][0], f[ch[i][0]][0] + f[ch[i][1]][0]);
        }
        printf("%d\n", f[ptot][1]);
    }
    return 0;
}