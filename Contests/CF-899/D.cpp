// D.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

int main()
{
    ll n;
    scanf("%lld", &n);
    ll upper = n + n - 1, acc = 0;
    while (acc * 10 + 9 <= upper)
        acc = acc * 10 + 9;
    ll lower = upper / (acc + 1), ans = 0;
    for (ll i = 0; i <= lower; i++)
    {
        ll merged = i * (acc + 1) + acc;
        if (merged <= n)
        {
            ans += (merged >> 1);
            if (merged % 2 == 0 && merged > 0)
                ans--;
        }
        else if (merged - n < n)
        {
            ll stpos = merged - n;
            ans += (n - stpos + 1) >> 1;
        }
    }
    printf("%lld", ans);
    return 0;
}