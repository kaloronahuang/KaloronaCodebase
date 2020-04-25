// P6185.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

typedef long long ll;

int T, n, m, ai[MAX_N], aff[MAX_N], ui[MAX_N], vi[MAX_N], etot, sum[MAX_N], ncnt, colors[MAX_N];
bool tag[MAX_N];
vector<int> G[MAX_N], V[MAX_N];

void dfsColor(int u, int col)
{
    aff[u] = col, sum[col] += ai[u];
    for (int v : G[u])
        if (aff[v] == 0)
            dfsColor(v, col);
}

bool dfsBinary(int u, int col, bool &bypassTrueTag, ll &sum1, ll &sum2)
{
    if (colors[u] != -1)
        return col == colors[u];
    colors[u] = col;
    bool ret = true;
    if (col == 0)
        sum1 += sum[u];
    else
        sum2 += sum[u];
    bypassTrueTag |= tag[u];
    for (int v : V[u])
        ret &= dfsBinary(v, col ^ 1, bypassTrueTag, sum1, sum2);
    return ret;
}

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &n, &m), ncnt = etot = 0;
        for (int i = 1; i <= n; i++)
            scanf("%d", &ai[i]);
        for (int i = 1, x; i <= n; i++)
            scanf("%d", &x), ai[i] = x - ai[i], G[i].clear(), sum[i] = aff[i] = tag[i] = 0, colors[i] = -1, V[i].clear();
        for (int i = 1, opt, u, v; i <= m; i++)
        {
            scanf("%d%d%d", &opt, &u, &v);
            if (opt == 1)
                ui[++etot] = u, vi[etot] = v;
            else
                G[u].push_back(v), G[v].push_back(u);
        }
        for (int i = 1; i <= n; i++)
            if (aff[i] == 0)
                dfsColor(i, ++ncnt);
        for (int i = 1; i <= etot; i++)
            if (aff[ui[i]] == aff[vi[i]])
                tag[aff[ui[i]]] = true;
            else
                V[aff[ui[i]]].push_back(aff[vi[i]]), V[aff[vi[i]]].push_back(aff[ui[i]]);
        bool ans = true;
        for (int i = 1; i <= ncnt; i++)
            if (colors[i] == -1)
            {
                bool bypass = false;
                ll sum1 = 0, sum2 = 0;
                if (dfsBinary(i, 0, bypass, sum1, sum2))
                    // bipart;
                    if (bypass)
                        ans &= (sum1 + sum2) % 2 == 0;
                    else
                        ans &= (sum1 == sum2);
                // exists odd loop with even length;
                else
                    ans &= (sum1 + sum2) % 2 == 0;
            }
        puts(ans ? "YES" : "NO");
    }
    return 0;
}