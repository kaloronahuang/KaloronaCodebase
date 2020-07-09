// CF662A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e5 + 200;

typedef long long ll;

int n, bcnt;
ll ai[MAX_N], bi[MAX_N], ci[MAX_N], S, base[200];

bool insert(ll x)
{
	for (int i = 1; i <= bcnt + 1; i++)
		x = min(x, x ^ base[i]);
	if (x > 0)
		base[++bcnt] = x;
	return x > 0;
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%lld%lld", &ai[i], &bi[i]), S ^= ai[i], insert(ai[i] ^ bi[i]);
	if (insert(S))
		puts("1/1");
	else
		printf("%lld/%lld\n", (1LL << bcnt) - 1, 1LL << bcnt);
	return 0;
}
