// YBT-OJ1674.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e6 + 200;

int hi[MAX_N], cnt[MAX_N], n, bi[MAX_N];

inline char gc()
{
    static const int IN_LEN = (1 << 20);
    static char buf[IN_LEN], *s, *t;
    return (s == t ? t = (s = buf) + fread(buf, 1, IN_LEN, stdin), (s == t ? -1 : *s++) : *s++);
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
    return x * f;
}

int main()
{
    n = read();
    for (int i = 1; i <= n; i++)
        hi[i] = read(), cnt[hi[i]]++;
    for (int i = 1; i <= n; i++)
        bi[cnt[i]]++;
    int lcur, mcur, rcur, ans = 0;
    for (lcur = n; lcur >= 1; lcur--)
        if (bi[lcur])
            break;
    for (mcur = lcur; mcur >= 1; mcur--)
        if (bi[mcur] && (bi[mcur] >= 2 || mcur != lcur))
            break;
    for (rcur = mcur; rcur >= 1; rcur--)
        if (bi[rcur] && (bi[rcur] >= ((mcur == lcur) ? 3 : 2) || rcur != mcur))
            break;
    while (lcur != 0 && mcur != 0 && rcur != 0)
    {
        ans++;
        bi[lcur]--, bi[lcur - 1]++;
        bi[mcur]--, bi[mcur - 1]++;
        bi[rcur]--, bi[rcur - 1]++;
        while (bi[lcur] == 0 && lcur > 0)
            lcur--;
        while (((bi[mcur] == 0) || (mcur == lcur && bi[lcur] == 1)) && mcur > 0)
            mcur--;
        while (((bi[rcur] == 0) || (lcur == mcur && mcur == rcur && bi[lcur] == 2) || (lcur != mcur && mcur == rcur && bi[rcur] == 1)) && rcur > 0)
            rcur--;
    }
    printf("%d\n", ans);
    return 0;
}