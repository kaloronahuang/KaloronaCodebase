// lucky.cpp
#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

int n, base_xor, ans = -2e9, ans_pos = -2e9;
vector<pii> bucket;
map<int, int> mp;

void fileIO()
{
	freopen("lucky.in", "r", stdin);
	freopen("lucky.out", "w", stdout);
}

void update_pos(int x)
{
	if (abs(x) < abs(ans_pos))
		ans_pos = x;
	else if (abs(x) == abs(ans_pos) && x > ans_pos)
		ans_pos = x;
}

int main()
{
	fileIO();
	scanf("%d", &n);
	for (int i = 1, opt, l, r, v; i <= n; i++)
	{
		scanf("%d%d", &opt, &l);
		if (opt == 1)
			scanf("%d%d", &r, &v), r++;
		else
		{
			r = l + 1, scanf("%d", &v);
			if (opt == 3)
				base_xor ^= v;
		}
		mp[l] ^= v, mp[r] ^= v;
		// bucket.push_back(make_pair(l, v)), bucket.push_back(make_pair(r, v));
	}
	for (map<int, int>::iterator it = mp.begin(); it != mp.end(); it++)
		bucket.push_back(make_pair(it->first, it->second));
	bucket.push_back(make_pair(-0x3f3f3f3f, 0)), bucket.push_back(make_pair(0x3f3f3f3f, 0));
	sort(bucket.begin(), bucket.end());
	int pre = base_xor;
	for (int i = 0, siz = bucket.size(); i < siz - 1; i++)
	{
		pii curt = bucket[i];
		pre ^= curt.second;
		if (pre > ans)
		{
			ans = pre;
			ans_pos = curt.first, update_pos(bucket[i + 1].first - 1);
			if (curt.first <= 0 && 0 <= bucket[i + 1].first - 1)
				ans_pos = 0;
		}
		else if (pre == ans)
		{
			update_pos(curt.first), update_pos(bucket[i + 1].first - 1);
			if (curt.first <= 0 && 0 <= bucket[i + 1].first - 1)
				ans_pos = 0;
		}
	}
	printf("%d %d\n", ans, ans_pos);
	return 0;
}
