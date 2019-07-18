// D.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

ll T, n, k;

int main()
{
    scanf("%lld", &T);
    while (T--)
    {
        scanf("%lld%lld", &n, &k);
        ll num = 6;
        k -= 2;
        while (k > 3)
            k >>= 1, num <<= 1;
        if (n % num == 0)
            puts("Bob");
        else
            puts("Alice");
    }
    return 0;
}