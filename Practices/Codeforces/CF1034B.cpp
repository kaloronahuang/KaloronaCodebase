// CF1034B.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll n, m;

int main()
{
    scanf("%lld%lld", &n, &m);
    if (n > m)
        swap(n, m);
    long long ans = 0;
    if (n == 1)
        ans = 6LL * ll(m / 6) + 2LL * max(m % 6 - 3, 0LL);
    else if (n == 2)
    {
        if (m == 2)
            ans = 0;
        else if (m == 3)
            ans = 4;
        else if (m == 7)
            ans = 12;
        else
            ans = m * n;
    }
    else
        ans = 1LL * n * m;
    printf("%lld\t", ans ^ (ans & 1LL));
    return 0;
}