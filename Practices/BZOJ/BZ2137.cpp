// BZ2137.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, mod = 1000000007;

typedef long long ll;

ll n, m, ci[MAX_N], prefix[MAX_N], mat[110][110];

ll fpow(ll bas, ll tim)
{
    ll ret = 1;
    while (tim)
    {
        if (tim & 1)
            ret = 1LL * ret * bas % mod;
        bas = 1LL * bas * bas % mod;
        tim >>= 1;
    }
    return ret;
}

int main()
{
    scanf("%lld%lld", &n, &m);
    for (ll i = 1; i <= n; i++)
        scanf("%lld", &ci[i]);
    if (m <= 12)
    {
        for (ll i = 1; i <= m + 1; i++)
        {
            for (ll j = 1; j <= m + 1; j++)
                mat[i][j] = fpow(i, j);
            for (ll j = 1; j <= i; j++)
                mat[i][m + 2] = (0LL + mat[i][m + 2] + fpow(j, m)) % mod;
        }
        for (ll i = 1; i <= m + 1; i++)
        {
            ll key = 0;
            for (ll j = i; j <= m + 1 && key == 0; j++)
                if (mat[j][i] != 0)
                    key = j;
            if (key != i)
                for (ll j = i; j <= m + 2; j++)
                    swap(mat[i][j], mat[key][j]);
            ll inv = fpow(mat[i][i], mod - 2);
            for (ll j = i; j <= m + 2; j++)
                mat[i][j] = 1LL * mat[i][j] * inv % mod;
            for (ll j = 1; j <= m + 1; j++)
                if (i != j)
                {
                    ll rate = mat[j][i];
                    for (ll k = i; k <= m + 2; k++)
                        mat[j][k] = (0LL + mat[j][k] + mod - 1LL * rate * mat[i][k] % mod) % mod;
                }
        }
        ll ans = 1;
        for (ll i = 1; i <= n; i++)
        {
            ll pans = 0;
            for (ll j = 1; j <= m + 1; j++)
                pans = (0LL + pans + 1LL * mat[j][m + 2] * fpow((0LL + ci[i] + 1) % mod, j) % mod) % mod;
            ans = 1LL * ans * pans % mod;
        }
        printf("%lld\n", ans);
    }
    else
    {
        ll upper = *max_element(ci + 1, ci + 1 + n), ans = 1;
        for (ll i = 1; i <= upper + 5; i++)
            prefix[i] = (0LL + prefix[i - 1] + fpow(i, m)) % mod;
        for (ll i = 1; i <= n; i++)
            ans = 1LL * ans * prefix[ci[i] + 1] % mod;
        printf("%lld\n", ans);
    }
    return 0;
}