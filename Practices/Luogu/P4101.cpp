// P4101.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

ll T, n, m;

int main()
{
    scanf("%lld", &T);
    while (T--)
    {
        scanf("%lld%lld", &n, &m);
        ll tim = (n / m) * (m - 1) + ((n % m == 0) ? 0 : (n % m - 1));
        if (tim & 1)
            puts("0");
        else
            puts("1");
    }
    return 0;
}