// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int T, n, d[MAX_N];

inline long long Qjy(long long u) { return u * (u - 1); }

int main()
{
    for (int i = 1; i < MAX_N; i++)
        for (int j = i; j < MAX_N; j += i)
            d[j]++;
    scanf("%d", &T);
    while (T--)
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        int ga = __gcd(b, c), gb = __gcd(c, a), gc = __gcd(a, b), gg = __gcd(gc, c);
        printf("%lld\n", d[a] * d[b] * d[c] - (d[a] * Qjy(d[ga]) + d[b] * Qjy(d[gb]) + d[c] * Qjy(d[gc]) >> 1) + (Qjy(d[gg]) * (d[gg] - 2) / 3 << 1) + (Qjy(d[gg]) * (d[ga] + d[gb] + d[gc] - 3 * d[gg] + 2) >> 1) - (d[ga] - d[gg]) * (d[gb] - d[gg]) * (d[gc] - d[gg]));
    }
    return 0;
}