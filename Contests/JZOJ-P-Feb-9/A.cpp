// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, mod = 1e9 + 7;

int n, m, q, col[MAX_N], row[MAX_N], dist[2000][2000];
char cmdlet[10];

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

int getId(int i, int j) { return (1LL * (i - 1) * m % mod + j) % mod; }

namespace Subtask1
{

struct fenwick
{
    int nodes[MAX_N];

    inline int lowbit(int x) { return x & (-x); }

    void update(int x, int d)
    {
        for (; x <= max(n, m); x += lowbit(x))
            nodes[x] = (0LL + nodes[x] + mod + d) % mod;
    }

    int query(int x, int ret = 0)
    {
        for (; x; x -= lowbit(x))
            ret = (0LL + ret + nodes[x]) % mod;
        return ret;
    }
} tr[2];

void subtask1Handler()
{
    // if all k = 0;
    for (int i = 1; i <= n; i++)
        tr[0].update(i, row[i]);
    for (int i = 1; i <= m; i++)
        tr[1].update(i, col[i]);
    while (q--)
    {
        int x, y, xs, ys, k;
        scanf("%s%d%d", cmdlet + 1, &x, &y);
        if (cmdlet[1] == 'R')
            tr[0].update(x, -row[x]), tr[0].update(y, -row[y]), swap(row[x], row[y]), tr[0].update(x, row[x]), tr[0].update(y, row[y]);
        else if (cmdlet[1] == 'C')
            tr[1].update(x, -col[x]), tr[1].update(y, -col[y]), swap(col[x], col[y]), tr[1].update(x, col[x]), tr[1].update(y, col[y]);
        else
        {
            scanf("%d%d%d", &xs, &ys, &k);
            int r_len = xs - x + 1, c_len = ys - y + 1;
            int a = (1LL * (0LL + tr[0].query(xs) + mod - tr[0].query(x - 1)) % mod * (ys - y + 1) % mod + mod - 1LL * r_len * c_len % mod) % mod * m % mod;
            int b = 1LL * (0LL + tr[1].query(ys) + mod - tr[1].query(y - 1)) % mod * (xs - x + 1) % mod;
            printf("%lld\n", (0LL + a + b) % mod);
        }
    }
}

} // namespace Subtask1

int main()
{
    freopen("matrix.in", "r", stdin);
    freopen("matrix.out", "w", stdout);
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= n; i++)
        row[i] = i;
    for (int i = 1; i <= m; i++)
        col[i] = i;
    int level = max(n, max(m, q));
    Subtask1::subtask1Handler();
    return 0;
}