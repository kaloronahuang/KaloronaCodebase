// exCRT.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

typedef long long ll;

int n;

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
	x = y, y = tmp - (a / b) * y;
	return d;
}

int main()
{
	ll Mod, ans;
	scanf("%d%lld%lld", &n, &Mod, &ans);
	for (int i = 2; i <= n; i++)
	{
		ll a, b, x, y, d;
		scanf("%lld%lld", &a, &b);
		ll delta = ((b - ans) % a + a) % a;
		d = exgcd(Mod, a, x, y);
		x = fmul(x, delta / d, a);
		ans += Mod * x;
		Mod *= a / d, ans = (ans + Mod) % Mod;
	}
	printf("%lld\n", ans);
	return 0;
}
