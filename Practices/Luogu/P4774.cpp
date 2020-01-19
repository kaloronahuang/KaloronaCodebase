// P4774.cpp
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAX_N = 1e5 + 200;

int T, n, m;
ll ai[MAX_N], pi[MAX_N], attack_val[MAX_N], ci[MAX_N], xi[MAX_N], yi[MAX_N];
multiset<ll> ms;

ll multiply(ll a, ll b, ll mod)
{
    ll ret = 0;
    for (; b; b >>= 1, a = (a + a) % mod)
        if (b & 1)
            ret = (ret + a) % mod;
    return ret;
}

ll exgcd(ll a, ll b, ll &x, ll &y)
{
    if (b == 0)
    {
        x = 1, y = 0;
        return a;
    }
    ll d = exgcd(b, a % b, x, y), t = x;
    x = y, y = t - (a / b) * y;
    return d;
}

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &n, &m), ms.clear();
        for (int i = 1; i <= n; i++)
            scanf("%lld", &ai[i]);
        for (int i = 1; i <= n; i++)
            scanf("%lld", &pi[i]);
        for (int i = 1; i <= n; i++)
            scanf("%lld", &attack_val[i]);
        for (ll i = 1, val; i <= m; i++)
            scanf("%lld", &val), ms.insert(val);
        ll max_bound = 0, mod = 1, x = 0;
        bool flag = true;
        for (int rd = 1; rd <= n; rd++)
        {
            multiset<ll>::iterator it = ms.upper_bound(ai[rd]);
            if (it != ms.begin())
                it--;
            ll coeff = *it;
            ms.erase(it), ms.insert(attack_val[rd]), max_bound = max(max_bound, (ai[rd] - 1) / coeff + 1);
            // start to solve the equation;
            coeff %= pi[rd], ai[rd] %= pi[rd];
            if (coeff == 0 && ai[rd] > 0)
            {
                flag = false;
                break;
            }
            else if (coeff == 0 && ai[rd] == 0)
                continue;
            ll xi, yi, d = exgcd(coeff, pi[rd], xi, yi);
            if (ai[rd] % d != 0)
            {
                flag = false;
                break;
            }
            pi[rd] /= d, ai[rd] = multiply(ai[rd] / d, (xi % pi[rd] + pi[rd]) % pi[rd], pi[rd]);
            d = exgcd(mod, pi[rd], xi, yi);
            if ((ai[rd] - x) % d != 0)
            {
                flag = false;
                break;
            }
            mod = mod / d * pi[rd];
            x = (x + multiply(multiply(mod / pi[rd], (ai[rd] - x + mod) % mod, mod), (xi + mod) % mod, mod)) % mod;
        }
        if (flag)
            // output the answer;
            printf("%lld\n", (x >= max_bound) ? (x) : (x + mod * ((max_bound - x - 1) / mod + 1)));
        else
            puts("-1");
    }
    return 0;
}