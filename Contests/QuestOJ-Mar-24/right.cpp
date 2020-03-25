// right.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, q, p, ai[MAX_N];

inline char nc()
{
    static char buf[100000], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
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
    return x * f;
}

int cnt_p(int a)
{
    static int tmp1[30];
    memset(tmp1, 0, sizeof(tmp1));
    int cnt1 = 0, ret = 0;
    while (a)
        tmp1[++cnt1] = a % p, a /= p;
    for (int i = 1; i <= cnt1; i++)
        ret += tmp1[i];
    return ret;
}

int main()
{
    n = read(), q = read(), p = read();
    for (int i = 1; i <= n; i++)
        ai[i] = read();
    while (q--)
    {
        int opt = read(), l = read(), r = read(), d;
        if (opt == 0)
        {
            d = read();
            for (int i = l; i <= r; i++)
                ai[i] += d;
        }
        else
        {
            int sum = 0;
            for (int i = l; i <= r; i++)
                sum += cnt_p(ai[i]);
            printf("%d\n", sum % 2 == 1);
        }
    }
    return 0;
}