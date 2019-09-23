// god.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

int seq[MAX_N], n, T;

struct ios
{
    inline char read()
    {
        static const int IN_LEN = 1 << 18 | 1;
        static char buf[IN_LEN], *s, *t;
        return (s == t) && (t = (s = buf) + fread(buf, 1, IN_LEN, stdin)), s == t ? -1 : *s++;
    }
    template <typename _Tp>
    inline ios &operator>>(_Tp &x)
    {
        static char c11, boo;
        for (c11 = read(), boo = 0; !isdigit(c11); c11 = read())
        {
            if (c11 == -1)
                return *this;
            boo |= c11 == '-';
        }
        for (x = 0; isdigit(c11); c11 = read())
            x = x * 10 + (c11 ^ '0');
        boo && (x = -x);
        return *this;
    }
} io;

int main()
{
    freopen("god.in", "r", stdin);
    freopen("god.out", "w", stdout);
    io >> T;
    while (T--)
    {
        io >> n;
        for (int i = 1; i <= n; i++)
            io >> seq[i];
        nth_element(seq + 1, seq + ((n + 1) >> 1), seq + 1 + n);
        printf("%d\n", seq[((n + 1) >> 1)]);
    }
    return 0;
}