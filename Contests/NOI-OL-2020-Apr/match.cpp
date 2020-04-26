// match.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5050, mod = 998244353;

int n, head[MAX_N], current, deg[MAX_N], siz[MAX_N], lft[MAX_N], rig[MAX_N], ptot;
char str[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void fileIO(string src)
{
    freopen((src + ".in").c_str(), "r", stdin);
    freopen((src + ".out").c_str(), "w", stdout);
}

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

namespace subtaskChain
{

int ans = 0;

int handler()
{
    for (int i = 0; i <= (n >> 1) - 1; i++)
        printf("0 ");
    int ans = 1;
    for (int i = 1; i <= (n >> 1); i++)
        ans = 1LL * ans * i % mod;
    printf("%d\n", ans);
    return 0;
}

} // namespace subtaskChain

namespace bruteForce
{

int idx1[MAX_N], idx2[MAX_N], ansBox[MAX_N];

int fpow(int bas, int tim)
{
    int ret = 1;
    while (tim)
    {
        if (tim & 1)
            ret = 1LL * ret * bas % mod;
        bas = 1LL * bas * bas % mod;
        tim >>= 1;
    }
    return ret;
}

void dfs(int u, int fa)
{
    lft[u] = ++ptot;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dfs(edges[i].to, u);
    rig[u] = ptot;
}

int handler()
{
    dfs(1, 0);
    for (int i = 1, cnt = 0; i <= n; i++)
        if (str[i] == '0')
            idx1[++cnt] = i;
    for (int i = 1, cnt = 0; i <= n; i++)
        if (str[i] == '1')
            idx2[++cnt] = i;
    do
    {
        int cnt = 0;
        for (int i = 1; i <= (n >> 1); i++)
            if ((lft[idx1[i]] <= lft[idx2[i]] && lft[idx2[i]] <= rig[idx1[i]]) || (lft[idx2[i]] <= lft[idx1[i]] && lft[idx1[i]] <= rig[idx2[i]]))
                cnt++;
        ansBox[cnt]++;
    } while (next_permutation(idx2 + 1, idx2 + 1 + (n >> 1)));
    for (int i = 0; i <= (n >> 1); i++)
        printf("%d ", ansBox[i]);
    return 0;
}

} // namespace bruteForce

int main()
{
    fileIO("match");
    memset(head, -1, sizeof(head));
    scanf("%d%s", &n, str + 1);
    for (int i = 1, u, v; i < n; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u), deg[u]++, deg[v]++;
    int cnt2 = 0, cnt1 = 0;
    for (int i = 1; i <= n; i++)
        cnt2 += (deg[i] == 2), cnt1 += (deg[i] == 1);
    if (cnt1 == 2 && cnt2 == n - 2 && deg[1] == 1)
        return subtaskChain::handler();
    // normal situation;
    return bruteForce::handler();
    return 0;
}