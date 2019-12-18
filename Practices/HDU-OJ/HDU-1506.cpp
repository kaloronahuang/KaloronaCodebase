// HDU-1506.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 1e5 + 200;

struct node
{
    int ch[2], idx, fa, val;
    void clear() { ch[0] = ch[1] = idx = fa = val = 0; }
} nodes[MAX_N];

int n, stk[MAX_N << 1], top;
ll ans;

int build()
{
    for (int i = 1; i <= n; i++)
    {
        int k = i - 1;
        while (nodes[k].val > nodes[i].val)
            k = nodes[k].fa;
        nodes[i].ch[0] = nodes[k].ch[1];
        nodes[k].ch[1] = i;
        nodes[i].fa = k, nodes[nodes[i].ch[0]].fa = i;
    }
    return nodes[0].ch[1];
}

int dfs(int u)
{
    if (u == 0)
        return 0;
    int siz = 1;
    for (int bit = 0; bit < 2; bit++)
        siz += dfs(nodes[u].ch[bit]);
    ans = max(ans, 1LL * siz * nodes[u].val);
    return siz;
}

int main()
{
    while (scanf("%d", &n) && n != 0)
    {
        ans = 0;
        nodes[0].ch[0] = nodes[0].ch[1] = nodes[0].idx = nodes[0].fa = nodes[0].val = 0;
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", &nodes[i].val), nodes[i].idx = i, nodes[i].fa = 0;
            memset(nodes[i].ch, 0, sizeof(nodes[i].ch));
        }
        dfs(build());
        printf("%lld\n", ans);
    }
    return 0;
}