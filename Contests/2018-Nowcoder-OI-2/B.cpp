// B.cpp
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main()
{
    ll n, m;
    scanf("%lld%lld", &n, &m);
    if (n < m)
        swap(n, m);
    if (m <= 2)
        printf("%lld", n * m);
    else if (m == 3)
        printf("%lld", n + 6 * (n / 6) + 2 * min(n % 6, 3LL));
    else if (m == 4)
    {
        if (n % 6 == 0)
            printf("%lld", 2 * n);
        else if (n % 6 == 1 || n % 6 == 2)
            printf("%lld", 12 * (n / 6) + 4 * (n % 6));
        else if (n % 6 == 3 || n % 6 == 4)
            printf("%lld", 12 * (n / 6) + 4 * 2 + 2 * ((n % 6) - 2));
        else
            printf("%lld", 12 * (n / 6) + 4 * 2 + 2 * 2);
    }
    else
        printf("%lld", (n * m + 1) / 2);
    return 0;
}