// password.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll C, limV, limE;

int main()
{
	scanf("%lld%lld%lld", &C, &limV, &limE);
	int n = 0;
	while ((1LL << n) < C)
		n++;
	ll acc = (1LL << n) - C;
	vector<pair<int, int> /**/> vec;
	for (int i = 1; i <= n; i++)
		vec.push_back(make_pair(i, i + 1));
	for (int i = 1; i <= n; i++)
		if (acc & (1LL << (n - i)))
			vec.push_back(make_pair(i, 1));
		else
			vec.push_back(make_pair(i, n + 1));
	printf("%d %d\n", n + 1, int(vec.size()));
	for (auto x : vec)
		printf("%d %d\n", x.second, x.first);
	return 0;
}