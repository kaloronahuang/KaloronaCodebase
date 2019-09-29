// COGS2498.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 11000, mod = 998244353;

int fib[MAX_N], seq[MAX_N], blocks[110][2], n, m, q;

int query(int x)
{
    int id = (x - 1) / m + 1, l1 = blocks[id][0], l2 = blocks[id][1];
    for (int i = (id - 1) * m + 2; i <= x; i++)
    {
        int y = (l1 + l2) % mod;
        l1 = l2, l2 = y;
    }
    return (1LL * (l1 + seq[x]) % mod + mod) % mod;
}

void update(int l, int r)
{
    int x = (l - 1) / m + 1, y = (r - 1) / m + 1;
    int bias1 = x * m - l, bias2 = y * m - r;
    for (int i = 0; i <= bias1; i++)
        seq[i + l] = (1LL * seq[i + l] + fib[i]) % mod;
    for (int i = 1; i <= bias2; i++)
        seq[i + r] = (1LL * seq[i + r] - fib[i + r - l] + mod) % mod;
    for (int i = x + 1; i <= y; i++)
    {
        blocks[i][0] = (1LL * blocks[i][0] + fib[bias1 + (i - x - 1) * m + 1]) % mod;
        blocks[i][1] = (1LL * blocks[i][1] + fib[bias1 + (i - x - 1) * m + 2]) % mod;
    }
}

int main()
{
    freopen("chenyao_fib_game.in", "r", stdin);
    freopen("chenyao_fib_game.out", "w", stdout);
    scanf("%d%d", &n, &q);
    m = sqrt(n - 1) + 1;
    fib[0] = fib[1] = 1;
    for (int i = 2; i <= n; i++)
        fib[i] = (1LL * fib[i - 1] + 1LL * fib[i - 2]) % mod;
    while (q--)
    {
        int opt, x, y;
        scanf("%d%d", &opt, &x);
        if (opt == 1)
            scanf("%d", &y), update(x, y);
        else
            printf("%d\n", query(x));
    }
    return 0;
}