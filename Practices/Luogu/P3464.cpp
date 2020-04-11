// P3464.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, mod = 1e9;

int n, digits[MAX_N], d4[MAX_N], len;
char str[MAX_N];

struct node
{
    int x, y;
} f[MAX_N], g[MAX_N];

node merge(node x, node y)
{
    if (x.x > y.x)
        swap(x, y);
    if (x.x == y.x)
        x.y = (0LL + x.y + y.y) % mod;
    return x;
}

node merge(node x, int y) { return node{x.x + y, x.y}; }

int main()
{
    scanf("%s", str), len = strlen(str);
    for (int i = 1; i <= len; i++)
        digits[i] = str[len - i] - '0';
    while (len)
    {
        digits[0] = 0;
        for (int i = len; i >= 1; i--)
            digits[i - 1] += (digits[i] & 3) * 10, digits[i] >>= 2;
        d4[++n] = digits[0] / 10;
        while (len && digits[len] == 0)
            len--;
    }
    f[0] = node{0, 1}, g[0] = node{n, 0};
    for (int i = 1; i <= n + 1; i++)
    {
        f[i] = merge(merge(f[i - 1], d4[i]), merge(g[i - 1], d4[i] + 1));
        g[i] = merge(merge(f[i - 1], 4 - d4[i]), merge(g[i - 1], 3 - d4[i]));
    }
    printf("%d\n", f[n + 1].y);
    return 0;
}