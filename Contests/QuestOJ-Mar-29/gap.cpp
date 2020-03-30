#include <bits/stdc++.h>
#include "gap.h"

using namespace std;

const int MAX_N = 1e5 + 200;

typedef long long ll;

ll seq[MAX_N];

long long findGap(int T, int N)
{
	if (T == 1)
	{
		ll L = 0, R = 1e18, ans = 0;
		int lptr = 1, rptr = N;
		while (lptr <= rptr)
			MinMax(L, R, &seq[lptr], &seq[rptr]), L = seq[lptr] + 1, R = seq[rptr] - 1, lptr++, rptr--;
		for (int i = 2; i <= N; i++)
			ans = max(ans, seq[i] - seq[i - 1]);
		return ans;
	}
	else
	{
		MinMax(0, 1e18, &seq[1], &seq[N]);
		ll ans = (seq[N] - seq[1]) / (N - 1), R = -1, ptr = seq[1];
		while (ptr <= seq[N])
		{
			ll cl, cr;
			MinMax(ptr, ptr + ans, &cl, &cr);
			ptr += ans + 1;
			if (R != -1 && cl != -1)
				ans = max(ans, cl - R);
			if (cr != -1)
				R = cr;
		}
		return ans;
	}
}