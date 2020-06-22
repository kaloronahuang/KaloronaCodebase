// LOJ2824.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 1e5 + 200;

int n;

ll solve(vector<int> req, bool flag)
{
	if (req.size() == 1)
	{
		int u = req[0];
		ll res = 0;
		for (int i = 1; i <= 9; i++)
			if (u & (1 << i))
			{
				res = res * 10LL + i, u ^= (1 << i);
				if (u & 1)
					res = 10LL * res, u ^= 1;
			}
		if (u & 1)
			res = 10;
		if (flag)
			res = max(res, 1LL);
		return res;
	}
	ll res = 1LL << 62;
	for (int b = 0; b <= 9; b++)
	{
		if (req.size() == 2 && (~req[0] >> 9 & 1) && (~req[1] & 1) && (!flag) && b == 9)
			continue;
		vector<int> nxt;
		for (int i = 0, y = b - 1, acc = 0, siz = req.size(); i < siz; i++)
		{
			y++, acc |= req[i] & (~(1 << y));
			if (y == 9 || i == siz - 1)
				nxt.push_back(acc), y = -1, acc = 0;
		}
		res = min(res, solve(nxt, (b == 0) && (req[0] & 1)) * 10 + b);
	}
	return res;
}

int main()
{
	scanf("%d", &n);
	vector<int> curt;
	for (int i = 1, v; i <= n; i++)
		scanf("%d", &v), curt.push_back(1 << v);
	printf("%lld\n", solve(curt, true));
	return 0;
}
