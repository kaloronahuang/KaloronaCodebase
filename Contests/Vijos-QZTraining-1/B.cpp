// B.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 1e5 + 200;
const ll mod = 199907210507;

struct node
{
    int ch[2];
    ll val;
} nodes[MAX_N * 70];

ll ptot = 1, n, arr[MAX_N], ans, pow2[70];

void insert(ll x)
{
    int p = 1;
    for (int i = 0; i <= 62; i++)
    {
        int bit = (x >> i) & 1;
        if (nodes[p].ch[bit] == 0)
            nodes[p].ch[bit] = ++ptot;
        nodes[p].val++, p = nodes[p].ch[bit];
    }
}

void dfs(int u, int cnt)
{
    if (u == 0)
        return;
    (ans += 1LL * nodes[nodes[u].ch[0]].val * nodes[nodes[u].ch[1]].val % mod * pow2[cnt]) %= mod;
    dfs(nodes[u].ch[0], cnt + 1), dfs(nodes[u].ch[1], cnt + 1);
}

int main()
{
    scanf("%lld", &n);
    for (int i = pow2[0] = 1; i < 70; i++)
        pow2[i] = 1LL * pow2[i - 1] * 2 % mod;
    for (int i = 1; i <= n; i++)
        scanf("%lld", &arr[i]), insert(arr[i]);
    dfs(1, 0), printf("%lld", 1LL * ans * 2 % mod);
    return 0;
}