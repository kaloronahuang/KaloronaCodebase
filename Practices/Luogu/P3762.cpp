// P3762.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

const int MAX_N = 22, MAX_M = 1e4 + 200;

const int base[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

ll fmul(ll A, ll B, ll mod)
{
    ll ret = A * B - ((ll)((ld)A / mod * B + 0.5)) * mod;
    return ret < 0 ? ret + mod : ret;
}

ll fpow(ll bas, ll tim, ll mod)
{
	ll ret = 1;
	while (tim)
	{
		if (tim & 1)
			ret = fmul(ret, bas, mod);
		bas = fmul(bas, bas, mod);
		tim >>= 1;
	}
	return ret;
}

ll unifiedRand(ll l, ll r)
{
    static mt19937_64 seed(time(NULL) * (ll)(new int));
    return uniform_int_distribution<ll>(l, r)(seed);
}

bool millerRabin(ll curt)
{
	for (int ci = 0; ci < 12; ci++)
	{
		ll cbase = base[ci];
		if (cbase == curt)
			return true;
		else if (curt < cbase)
			return false;
		ll acc = fpow(cbase, curt - 1, curt), idx = curt - 1;
		if (acc != 1)
			return false;
		while (acc == 1 && idx % 2 == 0)
		{
			idx >>= 1, acc = fpow(cbase, idx, curt);
			if (acc != 1 && acc != curt - 1)
				return false;
		}
	}
	return true;
}

ll pollardRho(ll curt)
{
	if (curt % 2 == 0)
		return 2;
	if (curt % 3 == 0)
		return 3;
	ll x = 0, y = 0, c = unifiedRand(1, curt), bas = 1, unit = (1 << 7), factor = 1;
	for (ll step = 2; ; step <<= 1, y = x, bas = 1)
	{
		for (ll ptr = 1; ptr <= step; ptr++)
		{
			x = (fmul(x, x, curt) + c) % curt, bas = fmul(bas, abs(x - y), curt);
			if (ptr % unit == 0)
			{
				factor = __gcd(bas, curt);
				if (factor > 1)
					return factor;
			}
		}
		if (factor > 1 || ((factor = __gcd(bas, curt)) > 1))
			return factor;
	}
	return curt;
}

void factorize(ll curt, vector<ll> &fac)
{
	if (curt == 1)
		return;
	if (millerRabin(curt))
		return (void)(fac.push_back(curt));
	ll p = curt;
	while (p >= curt)
		p = pollardRho(curt);
	factorize(curt / p, fac), factorize(p, fac);
}

ll n, m, q, ai[MAX_N][MAX_M], icnt[MAX_M];

int main()
{
	scanf("%lld%lld%lld", &n, &m, &q);
	for (int i = 0; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf("%lld", &ai[i][j]);
	while (q--)
	{
		int idx;
		ll mod, phi;
		scanf("%d%lld", &idx, &mod);
		vector<ll> fac;
		factorize(mod, fac), sort(fac.begin(), fac.end()), fac.erase(unique(fac.begin(), fac.end()), fac.end());
		phi = mod;
		for (ll p : fac)
			phi = phi - phi / p;
		memset(icnt, 0, sizeof(icnt));
		ll ans = 1, inv = 1;
		for (int i = 1; i <= m; i++)
		{
			ll x = ai[0][i], ptr = 0;
			for (ll p : fac)
			{
				while (x % p == 0)
					x /= p, icnt[ptr]++;
				ptr++;
			}
			ans = fmul(ans, x, mod);
		}
		for (ll i = 1; i <= m; i++)
		{
			ll x = ai[idx][i], ptr = 0;
			for (ll p : fac)
			{
				while (x % p == 0)
					x /= p, icnt[ptr]--;
				ptr++;
			}
			inv = fmul(inv, x, mod);
		}
		int fsiz = fac.size();
		if (*min_element(icnt, icnt + fsiz) < 0)
			puts("-1");
		else
		{
			for (int i = 0; i < fsiz; i++)
				ans = fmul(ans, fpow(fac[i], icnt[i], mod), mod);
			ans = fmul(ans, fpow(inv, phi - 1, mod), mod);
			printf("%lld\n", ans);
		}
	}
	return 0;
}
