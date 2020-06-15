// Redsun.cpp
#include <bits/stdc++.h>

using namespace std;

const int mod = 1e9 + 7;

typedef long long ll;

int f(ll n, ll a, ll c)
{
	if (n == 0 || a == 0)
		return 0;
	double verdict = 1.0 * a / c;
	if (verdict >= 1)
		return (1LL * n * (n + 1) / 2 % mod * (ll(a / c) % mod) % mod + f(n, a - ll(a / c) * c, c)) % mod;
	else
	{
		int ret = (1LL * n * (ll(1LL * a * n / c) % mod) % mod + mod - f(1LL * n * a / c, c, a)) % mod;
		ll ext = (1LL * a * n / c) / (a / __gcd(a, c));
		return (0LL + ret + ext % mod) % mod;
	}
}

int n, a, c;

int main()
{
	scanf("%d%d%d", &n, &a, &c);
	printf("%d\n", f(n, a, c));
	return 0;
}
