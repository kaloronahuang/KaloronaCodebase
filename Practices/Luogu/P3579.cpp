// P3579.cpp
#include <bits/stdc++.h>

using namespace std;

int T, smin, smax, wmin, wmax;

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
    return x * f;
}

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        smin = read(), smax = read(), wmin = read(), wmax = read();
        smin--, wmin--;
        int ans = 0;
        for (int d = 1, gx; d <= min(smax, wmax); d = gx + 1)
        {
            gx = min({smax / (smax / d), wmax / (wmax / d)});
            if (int(smin / d) != 0)
                gx = min(gx, smin / (smin / d));
            if (int(wmin / d) != 0)
                gx = min(gx, wmin / (wmin / d));
            if ((smax / d) - (smin / d) > 0 && (wmax / d) - (wmin / d) > 0)
                ans = gx;
        }
        printf("%d\n", ans);
    }
    return 0;
}