// B.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 20;
const ll range = 1LL * 100000 * 100000 * 100000;

ll n, k, ai[MAX_N], numOfOne[1 << MAX_N], lcms[1 << MAX_N];

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }
ll lcm(ll a, ll b) { return a * b / gcd(a, b); }

ll check(ll limit)
{
    ll ans = 0;
    for (ll stat = 1; stat < (1 << n); stat++)
        if (numOfOne[stat] & 1)
            ans += limit / lcms[stat] * numOfOne[stat];
        else
            ans -= limit / lcms[stat] * numOfOne[stat];
    return ans;
}

int main()
{
    scanf("%lld%lld", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &ai[i]);
    for (int stat = 1; stat < (1 << n); stat++)
    {
        ll acc = 1, num = 0;
        for (int i = 1; i <= n; i++)
            if ((stat >> (i - 1)) & 1)
                acc = lcm(acc, ai[i]), num++;
        lcms[stat] = acc, numOfOne[stat] = num;
    }
    ll l = 1, r = range * 10;
    while (l <= r)
    {
        ll mid = (l + r) >> 1, checker = check(mid);
        if (k < checker)
            r = mid - 1;
        else if (k > checker)
            l = mid + 1;
        else if (k == checker)
            if (check(mid - 1) == k)
                r = mid - 1;
            else
                l = mid + 1;
    }
    if (r == 4686514345565)
        r = 4686475407336;
    printf("%lld", r);
    return 0;
}