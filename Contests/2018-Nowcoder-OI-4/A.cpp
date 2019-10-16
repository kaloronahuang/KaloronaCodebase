// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 110;

int n, m, q;
int sols[int(1e7 + 200)], tot, fa[MAX_N];
bool vis[MAX_N];

struct edge
{
    int from, to, weight;
} edges[MAX_N << 1];

int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v, w; i <= m; i++)
        scanf("%d%d%d", &u, &v, &w), edges[i] = edge{u, v, w};

    for (int i = 0; i < (1 << m); i++)
        if (__builtin_popcount(i) == n - 1)
        {
            bool flag = true;
            int acc = 0;
            for (int j = 1; j <= n; j++)
                fa[j] = j;
            for (int j = 1; j <= m; j++)
                if (i & (1 << (j - 1)))
                {
                    if (find(edges[j].from) == find(edges[j].to))
                    {
                        flag = false;
                        break;
                    }
                    fa[find(edges[j].from)] = find(edges[j].to);
                    acc += edges[j].weight;
                }
            if (flag)
                sols[++tot] = acc;
        }

    sort(sols + 1, sols + 1 + tot);
    /*
    printf("Solution num: %d\n", tot);
    for (int i = 1; i <= tot; i++)
        printf("%d ", sols[i]);
    puts("");
    */
    scanf("%d", &q);
    while (q--)
    {
        int lft, rig;
        scanf("%d%d", &lft, &rig);
        int pos1 = lower_bound(sols + 1, sols + 1 + tot, lft) - sols;
        int pos2 = upper_bound(sols + 1, sols + 1 + tot, rig) - sols;
        printf("%d\n", pos2 - pos1);
    }
    return 0;
}