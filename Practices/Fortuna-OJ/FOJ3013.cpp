// B.cpp
#include <bits/stdc++.h>
#define ll long long

const ll modulo = 1000000007;

using namespace std;

ll quick_pow(ll bas, ll tim)
{
	bas %= modulo;
	ll ans = 1;
	while(tim)
	{
		if(tim & 1)
			ans = ans * bas % modulo;
		bas = bas * bas % modulo;
		tim >>= 1;
	}
	return ans;
}

int main()
{
	ll x_w, y_h;
	scanf("%lld%lld", &x_w, &y_h);
	printf("%lld", 24LL * ((quick_pow(2, x_w - 2) + quick_pow(2, y_h - 2) - 1) % modulo) % modulo);
	return 0;
}
