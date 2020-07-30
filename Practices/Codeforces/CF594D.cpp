// CF594D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200, RANGE = 1e6 + 200, mod = 1e9 + 7;

int n, q, primes[MAX_N], tot, ai[MAX_N], pid[RANGE], pre[MAX_N], pinv[MAX_N];
int preprod[MAX_N], euler[MAX_N], preptot, nodes[MAX_N << 2], ansBox[MAX_N];
bool vis[RANGE];
vector<int> qpos[MAX_N];

#define mid ((l + r) >> 1)
#define lson (p << 1)
#define rson ((p << 1) | 1)

struct queryInfo
{
    int l, r, id;
} queries[MAX_N];

void build(int l, int r, int p)
{
    nodes[p] = 1;
    if (l == r)
        return;
    build(l, mid, lson), build(mid + 1, r, rson);
}

void update(int qx, int l, int r, int p, int val)
{
    nodes[p] = 1LL * nodes[p] * val % mod;
    if (l == r)
        return;
    if (qx <= mid)
        update(qx, l, mid, lson, val);
    else
        update(qx, mid + 1, r, rson, val);
}

int query(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
        return nodes[p];
    int ret = 1;
    if (ql <= mid)
        ret = 1LL * ret * query(ql, qr, l, mid, lson) % mod;
    if (mid < qr)
        ret = 1LL * ret * query(ql, qr, mid + 1, r, rson) % mod;
    return ret;
}

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

void sieve()
{
    for (int i = 2; i < RANGE; i++)
    {
        if (!vis[i])
        {
            primes[++tot] = i, pid[i] = tot, euler[tot] = (mod + 1LL - fpow(i, mod - 2)) % mod;
            pinv[tot] = fpow(euler[tot], mod - 2);
        }
        for (int j = 1; j <= tot && 1LL * i * primes[j] < RANGE; j++)
        {
            vis[i * primes[j]] = true;
            if (i % primes[j] == 0)
                break;
        }
    }
}

int main()
{
    scanf("%d", &n), sieve(), preprod[0] = 1, build(1, n, 1);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    scanf("%d", &q);
    for (int i = 1; i <= q; i++)
        scanf("%d%d", &queries[i].l, &queries[i].r), queries[i].id = i, qpos[queries[i].r].push_back(i);
    for (int i = 1, acc; i <= n; i++)
    {
        acc = ai[i];
        int pacc = 1;
        for (int j = 1; j <= tot && 1LL * primes[j] * primes[j] <= acc; j++)
            if (acc % primes[j] == 0)
            {
                if (pre[j] != 0)
                    update(pre[j], 1, n, 1, pinv[j]);
                pre[j] = i, pacc = 1LL * pacc * euler[j] % mod;
                while (acc % primes[j] == 0)
                    acc /= primes[j];
            }
        if (acc > 1)
        {
            int j = pid[acc];
            if (pre[j] != 0)
                update(pre[j], 1, n, 1, pinv[j]);
            pre[j] = i, pacc = 1LL * pacc * euler[j] % mod;
        }
        preprod[i] = 1LL * preprod[i - 1] * ai[i] % mod;
        update(i, 1, n, 1, pacc);
        for (int x : qpos[i])
        {
            ansBox[queries[x].id] = 1LL * preprod[i] * fpow(preprod[queries[x].l - 1], mod - 2) % mod;
            ansBox[queries[x].id] = 1LL * ansBox[queries[x].id] * query(queries[x].l, n, 1, n, 1) % mod;
        }
    }
    for (int i = 1; i <= q; i++)
        printf("%d\n", ansBox[i]);
    return 0;
}