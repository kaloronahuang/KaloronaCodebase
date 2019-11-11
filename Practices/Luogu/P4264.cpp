// P4264.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 1e5 + 200;

int n;
map<int, int> mp;
ll acc, ans, forpts, last_y = -1;

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		acc += abs(a - b);
		// never be optimal;
		if (abs(a) > abs(a - b))
			continue;
		mp[b] += 2;
		if ((a < b && a < 0) || (a >= b && a >= 0))
			mp[0]--, mp[b << 1]--;
		if ((a < b && a >= 0) || (a >= b && a < 0))
			mp[(b - a) << 1]--, mp[a << 1]--;
	}
	ans = acc;
	for (map<int, int>::iterator it = mp.begin(); it != mp.end(); it++)
	{
		int rate = it->first, cnt = it->second;
		acc += forpts * (rate - last_y), last_y = rate, forpts += cnt;
		ans = min(ans, acc);
	}
	printf("%lld", ans);
	return 0;
}
