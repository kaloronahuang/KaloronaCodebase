// B.cpp
#include <bits/stdc++.h>
#define ull unsigned long long

using namespace std;

const int MAX_N = 2e5 + 200, bitnum = 133, mod1 = 1e9 + 7, mod2 = 1e9 + 9, bitlft = 23333, bitrig = 998443;

struct hash_val
{
    int val1, val2;

    hash_val operator+(const int &ch)
    {
        hash_val ret = *this;
        ret.val1 = (1LL * ret.val1 + mod1 + ch) % mod1;
        ret.val2 = (1LL * ret.val2 + mod2 + ch) % mod2;
        return ret;
    }

    hash_val operator+(const hash_val &ch)
    {
        hash_val ret = *this;
        ret.val1 = (1LL * ret.val1 + mod1 + ch.val1) % mod1;
        ret.val2 = (1LL * ret.val2 + mod2 + ch.val2) % mod2;
        return ret;
    }

    hash_val operator-(const hash_val &rhs)
    {
        hash_val ret = *this;
        ret.val1 = (0LL + ret.val1 + mod1 - rhs.val1) % mod1;
        ret.val2 = (0LL + ret.val2 + mod2 - rhs.val2) % mod2;
        return ret;
    }

    hash_val operator*(const int &rhs)
    {
        hash_val ret = *this;
        ret.val1 = 1LL * ret.val1 * rhs % mod1;
        ret.val2 = 1LL * ret.val2 * rhs % mod2;
        return ret;
    }

    hash_val operator*(const hash_val &rhs)
    {
        hash_val ret = *this;
        ret.val1 = 1LL * ret.val1 * rhs.val1 % mod1;
        ret.val2 = 1LL * ret.val2 * rhs.val2 % mod2;
        return ret;
    }

    bool operator==(const hash_val &target) const { return val1 == target.val1 && val2 == target.val2; }

    bool operator<(const hash_val &target) const { return val1 < target.val1 || (val1 == target.val1 && val2 < target.val2); }
};

int n, m, ch[MAX_N][2], siz[MAX_N], fa[MAX_N];
hash_val nodes[MAX_N], bpow[MAX_N];
map<hash_val, int> mp;
long long ans = 0;

void dfs(int u, int opt)
{
    siz[u] = 1;
    if (ch[u][0] != -1)
        dfs(ch[u][0], opt), siz[u] += siz[ch[u][0]];
    else
        ch[u][0] = 0;
    if (ch[u][1] != -1)
        dfs(ch[u][1], opt), siz[u] += siz[ch[u][1]];
    else
        ch[u][1] = 0;

    hash_val curt = hash_val{0, 0};
    curt = nodes[ch[u][0]] * nodes[ch[u][0]] * bitlft + nodes[ch[u][1]] * bitrig + (siz[u] ^ siz[ch[u][1]]);
    nodes[u] = curt;
    if (opt == 0)
        mp[nodes[u]]++;
    else
        ans += mp[nodes[u]];
}

void setFather(int x, int fat) { x > 0 ? fa[x] = fat : 0; }

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &ch[i][0], &ch[i][1]), setFather(ch[i][0], i), setFather(ch[i][1], i);
    bpow[0] = hash_val{1, 1};
    for (int i = 1; i <= max(n, m); i++)
        bpow[i] = bpow[i - 1] * bitnum;
    for (int i = n + 1; i <= n + m; i++)
    {
        scanf("%d%d", &ch[i][0], &ch[i][1]);
        if (ch[i][0] != -1)
            ch[i][0] += n;
        if (ch[i][1] != -1)
            ch[i][1] += n;
        setFather(ch[i][0], i), setFather(ch[i][1], i);
    }
    int root1, root2;
    for (int i = 1; i <= n; i++)
        if (fa[i] == 0)
            root1 = i;
    for (int i = n + 1; i <= n + m; i++)
        if (fa[i] == 0)
            root2 = i;
    dfs(root1, 0), dfs(root2, 1), printf("%lld\n", ans);
    return 0;
}