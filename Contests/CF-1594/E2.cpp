// E2.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, mod = 1e9 + 7, opp[6] = {1, 0, 3, 2, 5, 4};

typedef long long ll;

int k, n, nodes[MAX_N][2], ptot, dep[MAX_N], tag[MAX_N], dp[MAX_N][6];
char cmdlet[10];

int mapper(char c)
{
    switch (c)
    {
    case 'w':
        return 0;
    case 'y':
        return 1;
    case 'g':
        return 2;
    case 'b':
        return 3;
    case 'r':
        return 4;
    case 'o':
        return 5;
    }
    return -1;
}

int fpow(int bas, int tim, int modulo)
{
    int ret = 1;
    while (tim)
    {
        if (tim & 1)
            ret = 1LL * ret * bas % modulo;
        bas = 1LL * bas * bas % modulo;
        tim >>= 1;
    }
    return ret;
}

void insert(ll x, int typ)
{
    int p = 1;
    vector<int> seq;
    while (x)
        seq.push_back(x & 1LL), x >>= 1;
    seq.pop_back();
    reverse(seq.begin(), seq.end());
    for (int c : seq)
    {
        if (nodes[p][c] == 0)
            nodes[p][c] = ++ptot, dep[ptot] = dep[p] + 1;
        p = nodes[p][c];
    }
    tag[p] = typ;
}

void dfs(int u)
{
    int udp[2][6], sum[2];
    memset(udp, 0, sizeof(udp)), sum[0] = sum[1] = 0;
    for (int dir = 0; dir < 2; dir++)
        if (nodes[u][dir])
        {
            dfs(nodes[u][dir]);
            for (int d = 0; d < 6; d++)
                udp[dir][d] = dp[nodes[u][dir]][d];
        }
    for (int d = 0; d < 6; d++)
        sum[0] = (0LL + sum[0] + udp[0][d]) % mod, sum[1] = (0LL + sum[1] + udp[1][d]) % mod;
    for (int d = 0; d < 6; d++)
        if (d == tag[u] || tag[u] == -1)
        {

            int ls, rs;
            if (nodes[u][0] == 0)
                ls = fpow(4, (0LL + fpow(2, k - dep[u], mod - 1) + mod - 2) % (mod - 1), mod);
            else
                ls = (0LL + sum[0] + (mod - udp[0][d]) % mod + (mod - udp[0][opp[d]]) % mod) % mod;
            if (nodes[u][1] == 0)
                rs = fpow(4, (0LL + fpow(2, k - dep[u], mod - 1) + mod - 2) % (mod - 1), mod);
            else
                rs = (0LL + sum[1] + (mod - udp[1][d]) % mod + (mod - udp[1][opp[d]]) % mod) % mod;
            dp[u][d] = 1LL * ls * rs % mod;
        }
}

int main()
{
    memset(tag, -1, sizeof(tag)), dep[1] = ptot = 1;
    scanf("%d%d", &k, &n);
    for (ll i = 1, u; i <= n; i++)
        scanf("%lld%s", &u, cmdlet + 1), insert(u, mapper(cmdlet[1]));
    dfs(1);
    int ans = 0;
    for (int d = 0; d < 6; d++)
        ans = (0LL + ans + dp[1][d]) % mod;
    printf("%d\n", ans);
    return 0;
}