// P3471.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1010, MAX_L = 110, MAX_M = 2e5 + 200, base = 133, mod = 1e9 + 7;

typedef pair<int, int> pii;

int n, L, m, tree[MAX_N][MAX_L], basepow[MAX_L], ptot;
char str[MAX_N][MAX_L];
vector<pii> bucket[MAX_N];
map<int, int> mp, roots;

struct node
{
    int lson, rson, max_val;
} nodes[MAX_M * 30];

#define mid ((l + r) >> 1)

int update(int qx, int l, int r, int p, int val)
{
    if (p == 0)
        p = ++ptot;
    if (l == r)
        return (nodes[p].max_val = val, p);
    if (qx <= mid)
        nodes[p].lson = update(qx, l, mid, nodes[p].lson, val);
    else
        nodes[p].rson = update(qx, mid + 1, r, nodes[p].rson, val);
    nodes[p].max_val = max(nodes[nodes[p].lson].max_val, nodes[nodes[p].rson].max_val);
    return p;
}

int query(int ql, int qr, int l, int r, int p)
{
    if (p == 0)
        return 0;
    if (ql <= l && r <= qr)
        return nodes[p].max_val;
    int ret = 0;
    if (ql <= mid)
        ret = max(ret, query(ql, qr, l, mid, nodes[p].lson));
    if (mid < qr)
        ret = max(ret, query(ql, qr, mid + 1, r, nodes[p].rson));
    return ret;
}

inline int lowbit(int x) { return x & (-x); }

void update(int id, int x, int d)
{
    for (; x <= L; x += lowbit(x))
        tree[id][x] = (0LL + tree[id][x] + d) % mod;
}

int query(int id, int x, int ret = 0)
{
    for (; x; x -= lowbit(x))
        ret = (0LL + ret + tree[id][x]) % mod;
    return ret;
}

int main()
{
    scanf("%d%d%d", &n, &L, &m);
    for (int i = basepow[0] = 1; i <= L; i++)
        basepow[i] = 1LL * basepow[i - 1] * base % mod;
    for (int i = 1; i <= n; i++)
    {
        scanf("%s", str[i] + 1);
        for (int j = 1; j <= L; j++)
            update(i, j, 1LL * basepow[j] * (str[i][j] - 'a' + 1) % mod);
        int hash_val = query(i, L);
        bucket[i].push_back(make_pair(hash_val, 1)), mp[hash_val]++;
    }
    for (int i = 1, hash_val; i <= n; i++)
        hash_val = query(i, L), roots[hash_val] = update(1, 1, m, roots[hash_val], mp[hash_val]);
    for (int i = 1, a, b, c, d; i <= m; i++)
    {
        scanf("%d%d%d%d", &a, &b, &c, &d);
        mp[query(a, L)]--;
        if (a != c)
            mp[query(c, L)]--;
        roots[query(a, L)] = update(i, 1, m, roots[query(a, L)], mp[query(a, L)]);
        roots[query(c, L)] = update(i, 1, m, roots[query(c, L)], mp[query(c, L)]);

        update(a, b, (mod - 1LL * basepow[b] * (str[a][b] - 'a' + 1) % mod) % mod);
        update(c, d, (mod - 1LL * basepow[d] * (str[c][d] - 'a' + 1) % mod) % mod);
        swap(str[a][b], str[c][d]);
        update(a, b, 1LL * basepow[b] * (str[a][b] - 'a' + 1) % mod);
        update(c, d, 1LL * basepow[d] * (str[c][d] - 'a' + 1) % mod);

        mp[query(a, L)]++;
        if (a != c)
            mp[query(c, L)]++;

        roots[query(a, L)] = update(i, 1, m, roots[query(a, L)], mp[query(a, L)]);
        roots[query(c, L)] = update(i, 1, m, roots[query(c, L)], mp[query(c, L)]);

        bucket[a].push_back(make_pair(query(a, L), i));
        if (a != c)
            bucket[c].push_back(make_pair(query(c, L), i));
    }
    for (int i = 1, ans = 0; i <= n; i++, ans = 0)
    {
        for (int j = 0, siz = bucket[i].size(); j < siz; j++)
        {
            int l = bucket[i][j].second, r = (j == siz - 1) ? m : bucket[i][j + 1].second - 1, hash_val = bucket[i][j].first;
            ans = max(ans, query(l, r, 1, m, roots[hash_val]));
        }
        printf("%d\n", ans);
    }
    return 0;
}