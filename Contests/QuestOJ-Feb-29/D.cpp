// D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 2000;

int n, task, ai[MAX_N], g[20][MAX_N], f[20][MAX_N];
bool flag;

inline char nc()
{
    static char buf[1000000], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1000000, stdin), p1 == p2) ? EOF : *p1++;
}

int read()
{
    int x = 0, f = 1;
    char ch = nc();
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = nc();
    }
    while (isdigit(ch))
        x = (x << 3) + (x << 1) + ch - '0', ch = nc();
    return f * x;
}

int query(int l, int r)
{
    int ret = 0, acc = 0;
    for (int i = 19; i >= 0; i--)
        if (l + (1 << i) - 1 <= r)
        {
            ret ^= f[i][l];
            if (g[i][l])
                ret ^= acc;
            acc ^= (1 << i), l += (1 << i);
        }
    return ret;
}

int main()
{
    n = read(), task = read();
    for (int i = 1, x; i <= n; i++)
        x = read(), ai[x] ^= 1;
    for (int i = 1; i <= n; i++)
        g[0][i] = ai[i], ai[i] ^= ai[i - 1];
    for (int i = 1; i < 20; i++)
        for (int j = 0; j + (1 << i) - 1 <= n; j++)
            g[i][j] = ai[j + (1 << i) - 1] ^ (j == 0 ? 0 : ai[j - 1]);
    for (int i = 1; i < 20; i++)
        for (int j = 0; j + (1 << i) - 1 <= n; j++)
        {
            f[i][j] = f[i - 1][j] ^ f[i - 1][j + (1 << (i - 1))];
            if (g[i - 1][j + (1 << (i - 1))])
                f[i][j] ^= 1 << (i - 1);
        }
    for (int x = 1; x <= n; x++)
    {
        int res = 0;
        for (int i = 0; i <= n; i += (x + 1))
            res ^= query(i, min(n, i + x));
        if (res)
            puts("EncodeTalker");
        else
            puts("Kuruto");
    }
    return 0;
}