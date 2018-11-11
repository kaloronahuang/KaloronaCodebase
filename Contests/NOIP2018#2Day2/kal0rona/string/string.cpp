// string.cpp
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

#define ll long long
const ll mod = 1000000007;
const ll maxn = 4000;
ll a, b, c, d;
ll ans = 0;
ll C[maxn][maxn];

// note:
// num of T:C(c+d,d)

ll comb(ll n, ll m)
{
    if (n < m)
        return 0;
    return C[n][m];
}

int main()
{
    cin >> a >> b >> c >> d;
    C[0][0] = 1;
    for (ll i = 1; i < maxn; i++)
        C[i][1] = i % mod, C[i][i] = 1, C[i][0] = 1;
    for (ll n = 3; n < maxn; n++)
        for (ll m = 2; m < n; m++)
            C[n][m] = (C[n - 1][m - 1] + C[n - 1][m]) % mod;
    ll tmp = 0;
    for (ll i = (d == 0) ? a - c : 0; i <= a - c; i++)
        for (ll j = (c == 0) ? b - d : 0; j <= b - d; j++)
            tmp += ((((d == 0) ? 1 : (comb(a - c - i + d - 1, d - 1))) *
                     ((c == 0) ? 1 : comb(b - d - j + c - 1, c - 1))) %
                    mod * comb(i + j, i)) %
                   mod,
                tmp %= mod;
    ans = comb(c + d, c) * tmp % mod;
    cout << ans;
    return 0;
}