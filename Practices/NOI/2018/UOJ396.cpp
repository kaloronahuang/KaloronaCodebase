// UOJ396.cpp
#include <bits/stdc++.h>

using namespace std;

// #define DEB_MODE

const int MAX_N = 2e5 + 200;

typedef long long ll;
typedef multiset<ll>::iterator mit;

int T, n, m;
ll ai[MAX_N], pi[MAX_N], bounce[MAX_N], atk[MAX_N];

ll multiply(ll a, ll b, ll mod)
{
    ll ret = 0;
    while (b)
    {
        if (b & 1)
            ret = (0LL + ret + a) % mod;
        a = (0LL + a + a) % mod;
        b >>= 1;
    }
    return ret;
}

ll exgcd(ll a, ll b, ll &x, ll &y)
{
    if (b == 0)
    {
        x = 1, y = 0;
        return a;
    }
    ll d = exgcd(b, a % b, x, y), tmp = x;
    x = y, y = tmp - (a / b) * y;
    return d;
}

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }

int main()
{
    // freopen("ex_dragon2.in", "r", stdin);
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++)
            scanf("%lld", &ai[i]);
        for (int i = 1; i <= n; i++)
            scanf("%lld", &pi[i]);
        for (int i = 1; i <= n; i++)
            scanf("%lld", &bounce[i]);
        for (int i = 1; i <= m; i++)
            scanf("%lld", &atk[i]);
        ll lreq = 0, x = 0, Mod = 1;
        bool flag = true;
        multiset<ll> weapons;
        weapons.clear();
        for (int i = 1; i <= m; i++)
            weapons.insert(atk[i]);
        for (int i = 1; i <= n; i++)
        {
            mit cit = weapons.upper_bound(ai[i]);
            if (cit != weapons.begin())
                cit--;
            ll cw = *cit, srcai = ai[i];
            weapons.erase(cit), weapons.insert(bounce[i]);
            lreq = max(lreq, (ai[i] + cw - 1) / cw);
            // process the inv;
            // cw * x \equiv ai[i] \pmod pi[i];
            cw %= pi[i], ai[i] %= pi[i];
            if (cw == 0 && ai[i] != 0)
            {
                flag = false;
#ifdef DEB_MODE
                cout << "Inverse Problem : fatal on 0" << endl; // << cw << " at modulo domain " << pi[i] << endl;
#endif
                break;
            }
            else if (cw == 0 && ai[i] == 0)
                continue;
            ll ix, iy, id = exgcd(cw, pi[i], ix, iy);
            if (ai[i] % id != 0)
            {
                flag = false;
#ifdef DEB_MODE
                cout << "Inverse Problem : " << cw << " at modulo domain " << pi[i] << endl;
#endif
                break;
            }
            pi[i] /= id;
            ai[i] = multiply(ai[i] / id, (ix % pi[i] + pi[i]) % pi[i], pi[i]); // 1LL * ai[i] % pi[i] * (0LL + ix + pi[i]) % pi[i];
            // x \equiv ai[i] \pmod pi[i];
            ll y1, y2, delta = x - ai[i], yd = exgcd(Mod, pi[i], y1, y2);
            if (delta % yd != 0)
            {
                flag = false;
#ifdef DEB_MODE
                cout << "Merging Problem" << endl;
#endif
                break;
            }
            Mod = Mod / yd * pi[i];
            x = (x + multiply(multiply(Mod / pi[i], (ai[i] - x + Mod) % Mod, Mod), (y1 + Mod) % Mod, Mod)) % Mod;
        }
        if (!flag)
            puts("-1");
        else
            printf("%lld\n", x < lreq ? (x + (lreq - x + Mod - 1) / Mod * Mod) : x);
    }
    return 0;
}