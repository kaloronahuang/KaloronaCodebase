// 3.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int mod = 1e9 + 7;

int T;
ll xa, xb, ya, yb;

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%lld%lld%lld%lld", &xa, &xb, &ya, &yb);
        ll part1 = ((xb / xa) - ((xa - 1) / xa)) % mod * xa % mod;
        ll part2 = ((yb / ya) - ((ya - 1) / ya)) % mod * ya % mod;
        printf("%lld\n", 1LL * part1 * part2 % mod);
    }
    return 0;
}