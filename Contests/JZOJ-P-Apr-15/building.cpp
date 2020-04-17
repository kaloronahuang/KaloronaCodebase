// building.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

int n, hi[MAX_N], ai[MAX_N];

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

void fileIO()
{
    freopen("building.in", "r", stdin);
    freopen("building.out", "w", stdout);
}

int main()
{
    // fileIO();
    n = read();
    for (int i = 1; i <= n; i++)
        hi[i] = read();
    long long ans = 0;
    for (int i = 1; i <= n; i++)
    {
        hi[i] = max(hi[i], 0);
        int regret3 = min(hi[i] / 3, ai[i]);
        hi[i] -= regret3 * 3;
        int regret2 = hi[i] >> 1;
        hi[i] -= regret2 * 2;
        int regret1 = hi[i];
        hi[i] = 0, ans += regret1 + regret2 + regret3;
        ai[i + 1] += regret3 * 2 + regret2;
        hi[i + 1] -= regret2 + regret1 * 2;
    }
    printf("%lld\n", ans);
    return 0;
}