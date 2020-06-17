// P4655.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

typedef long long ll;
typedef long double ld;

int n, hi[MAX_N], wi[MAX_N], idx[MAX_N], stk[MAX_N], head, tail;
ll dp[MAX_N], Xi[MAX_N], Yi[MAX_N], pre[MAX_N];

ll pow2(ll x) { return 1LL * x * x; }

ld slope(int i, int j) { return (Xi[i] == Xi[j]) ? (Yi[j] - Yi[i]) * 1e50 : ld(Yi[j] - Yi[i]) / ld(Xi[j] - Xi[i]); }

void solve(int l, int r)
{
	if (l == r)
	{
		Yi[l] = 1LL * hi[l] * hi[l] - pre[l] + dp[l];
		return;
	}
	int mid = (l + r) >> 1;
	solve(l, mid);
	for (int i = l; i <= r; i++)
		idx[i] = i;
	sort(idx + l, idx + r + 1, [](const int &rhs1, const int &rhs2) { return Xi[rhs1] < Xi[rhs2]; });
	head = 1, tail = 0;
	for (int ptr = l; ptr <= r; ptr++)
	{
		int i = idx[ptr];
		if (i <= mid)
		{
			while (head < tail && slope(stk[tail], i) <= slope(stk[tail - 1], stk[tail]))
				tail--;
			stk[++tail] = i;
		}
	}
	for (int ptr = l; ptr <= r; ptr++)
	{
		int i = idx[ptr];
		if (i > mid)
		{
			while (head < tail && 2LL * hi[i] >= slope(stk[head], stk[head + 1]))
				head++;
			dp[i] = min(dp[i], dp[stk[head]] + pow2(hi[i] - hi[stk[head]]) + pre[i - 1] - pre[stk[head]]);
		}
	}
	solve(mid + 1, r);
}

int main()
{
	scanf("%d", &n), memset(dp, 0x3f, sizeof(dp)), dp[1] = 0;
	for (int i = 1; i <= n; i++)
		scanf("%d", &hi[i]), Xi[i] = hi[i];
	for (int i = 1; i <= n; i++)
		scanf("%d", &wi[i]), pre[i] = pre[i - 1] + wi[i];
	solve(1, n), printf("%lld\n", dp[n]);
	return 0;
}
