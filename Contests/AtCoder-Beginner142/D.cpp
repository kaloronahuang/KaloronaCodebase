#include <bits/stdc++.h>
#define int long long
using namespace std;
signed main()
{

    long long a, b;
    int i, gs = 0;
    int p[100];
    scanf("%lld%lld", &a, &b);
    long long n;
    n = __gcd(a, b);

    for (i = 2; i * i <= n; i++)
        if (n % i == 0)
        {
            p[gs++] = i;
            while (n % i == 0)
                n /= i;
        }
    if (n > 1)
        p[gs++] = n;
    gs++;
    printf("%d", gs);

    return 0;
}