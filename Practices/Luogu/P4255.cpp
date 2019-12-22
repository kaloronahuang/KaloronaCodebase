// P4255.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 4e5 + 2000, mod = 19260817, MDOM = MAX_N * 10;

int n, m, q, ni[MAX_N], ci[MAX_N], xi[MAX_N], yi[MAX_N], fac[MDOM];
int opt[MAX_N], A[MAX_N], B[MAX_N], C[MAX_N], fa[MAX_N], idx[MAX_N], ptot[MAX_N], ans[MAX_N], qtot;
bool vis[MAX_N];
map<int, int> mps[MAX_N];

int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

int quick_pow(int bas, int tim)
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

void unite(int x, int y)
{
    if (find(x) != find(y))
    {
        x = find(x), y = find(y);
        if (mps[idx[x]].size() < mps[idx[y]].size())
            swap(idx[x], idx[y]);
        for (map<int, int>::iterator it = mps[idx[y]].begin(); it != mps[idx[y]].end(); it++)
            mps[idx[x]][it->first] += it->second;
        ptot[x] += ptot[y], fa[y] = x;
    }
}

int main()
{
    scanf("%d%d%d", &n, &m, &q);
    for (int i = fac[0] = 1; i < MDOM; i++)
        fac[i] = 1LL * fac[i - 1] * i % mod;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", &ni[i], &ci[i]), fa[i] = i;
        idx[i] = i, mps[i][ci[i]] = ni[i], ptot[i] = ni[i];
    }
    for (int i = 1; i <= m; i++)
        scanf("%d%d", &xi[i], &yi[i]);
    for (int i = 1; i <= q; i++)
    {
        scanf("%d%d", &opt[i], &A[i]);
        if (opt[i] != 2)
        {
            scanf("%d%d", &B[i], &C[i]);
            if (opt[i] == 1)
                mps[idx[find(A[i])]][C[i]] += B[i], ptot[find(A[i])] += B[i];
        }
        else
            vis[A[i]] = true;
    }
    for (int i = 1; i <= m; i++)
        if (vis[i] == false && xi[i] != yi[i])
            unite(xi[i], yi[i]);
    for (int i = m; i >= 1; i--)
    {
        int op = opt[i], a = A[i], b = B[i], c = C[i];
        if (op == 1)
            mps[idx[find(a)]][c] -= b, ptot[find(a)] -= b;
        else if (op == 2)
            unite(xi[a], yi[a]);
        else
        {
            if (ptot[find(a)] - b < 0 || mps[idx[find(a)]][c] - b < 0)
                ans[++qtot] = 0;
            else
            {
                int upper = 1LL * fac[mps[idx[find(a)]][c]] * fac[ptot[find(a)] - b] % mod;
                int lower = 1LL * fac[ptot[find(a)]] * fac[mps[idx[find(a)]][c] - b] % mod;
                ans[++qtot] = 1LL * upper * quick_pow(lower, mod - 2) % mod;
            }
        }
    }
    for (int i = qtot; i >= 1; i--)
        printf("%d\n", ans[i]);
    return 0;
}