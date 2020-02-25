// LOJ3083.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1010, mod = 1e9 + 7;

int n, mat[32][MAX_N][MAX_N], ans1, ans2, tmp[32][MAX_N][MAX_N], stk[MAX_N], wi[MAX_N];

inline char gc()
{
    static char buf[1000000], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1000000, stdin), p1 == p2) ? EOF : *p1++;
}

int read()
{
    int x = 0, f = 1;
    char ch = gc();
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = gc();
    }
    while (isdigit(ch))
        x = (x << 3) + (x << 1) + ch - '0', ch = gc();
    return f * x;
}

int main()
{
    n = read();

    for (int i = 1; i <= n; i++)
        for (int j = 1, val; j <= n; j++)
        {
            val = read();
            for (int b = 0; b <= 30; b++)
                mat[b][i][j] = (val >> b) & 1;
        }
    int submat = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            submat = (0LL + submat + 1LL * i * j % mod) % mod;
    // or;
    for (int b = 0; b <= 30; b++)
    {
        int acc = 0;
        for (int i = 1; i <= n; i++)
        {
            int tail = 0, S = 0;
            for (int j = 1; j <= n; j++)
            {
                if (mat[b][i][j] == 1)
                    tmp[b][i][j] = 0;
                else
                    tmp[b][i][j] = 1 + tmp[b][i - 1][j];
                int w = 0;
                while (tail && tmp[b][i][j] < stk[tail])
                    S = (0LL + S + mod - 1LL * wi[tail] * stk[tail] % mod) % mod, w += wi[tail], tail--;
                w++, stk[++tail] = tmp[b][i][j], wi[tail] = w, S = (0LL + S + 1LL * w * stk[tail] % mod) % mod;
                acc = (0LL + acc + S) % mod;
            }
        }
        ans2 = (0LL + ans2 + 1LL * (0LL + submat + mod - acc) % mod * (1 << b) % mod) % mod;
    }
    for (int b = 0; b <= 30; b++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                mat[b][i][j] = 1 - mat[b][i][j];
    memset(tmp, 0, sizeof(tmp));
    for (int b = 0; b <= 30; b++)
    {
        int acc = 0;
        for (int i = 1; i <= n; i++)
        {
            int tail = 0, S = 0;
            for (int j = 1; j <= n; j++)
            {
                if (mat[b][i][j] == 1)
                    tmp[b][i][j] = 0;
                else
                    tmp[b][i][j] = 1 + tmp[b][i - 1][j];
                int w = 0;
                while (tail && tmp[b][i][j] < stk[tail])
                    S = (0LL + S + mod - 1LL * wi[tail] * stk[tail] % mod) % mod, w += wi[tail], tail--;
                w++, stk[++tail] = tmp[b][i][j], wi[tail] = w, S = (0LL + S + 1LL * w * stk[tail] % mod) % mod;
                acc = (0LL + acc + S) % mod;
            }
        }
        ans1 = (0LL + ans1 + 1LL * acc % mod * (1 << b) % mod) % mod;
    }
    printf("%d %d\n", ans1, ans2);
    return 0;
}