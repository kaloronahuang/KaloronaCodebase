// CRT.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 200;

ll n, bi[MAX_N], ai[MAX_N], ci[MAX_N], m;

ll fmul(ll a, ll b, ll cmod)
{
	ll ret = 0;
	while (b)
	{
		if (b & 1)
			ret = (0LL + ret + a) % cmod;
		a = (0LL + a + a) % cmod;
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
	x = y, y = tmp - y * (a / b);
	return d;
}

int main()
{
	scanf("%lld", &n), m = 1;
	for (int i = 1; i <= n; i++)
		scanf("%lld%lld", &ai[i], &bi[i]), m *= ai[i];
	for (int i = 1; i <= n; i++)
	{
		ll t = m / ai[i], x, y;
		exgcd(t, ai[i], x, y);
		ll inv = (x + ai[i]) % ai[i];
		ci[i] = 1LL * t * inv % m;
		// printf("%lld %lld %lld %lld\n", t, x, inv, ci[i]);
	}
	ll ans = 0;
	for (int i = 1; i <= n; i++)
		ans = (0LL + ans + fmul(bi[i], ci[i], m)) % m;
	printf("%lld\n", ans);
	return 0;
}
