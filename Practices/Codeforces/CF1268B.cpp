// CF1268B.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 3e5 + 2000;

ll n, ai[MAX_N], d, ans;

int main()
{
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld", &ai[i]), ans += ai[i];
        d += (1 - 2 * (i & 1)) * ai[i] % 2;
    }
    printf("%lld\n", (ans - abs(d)) >> 1);
    return 0;
}