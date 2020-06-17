// LOJ3277.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

typedef pair<int, int> pii;
typedef long long ll;

int n, m, hi[MAX_N], siz[MAX_N], ch[MAX_N][2], log2_[MAX_N], q[MAX_N], tail;
int X[MAX_N], Y[MAX_N], C[MAX_N], lft[2][MAX_N], rig[2][MAX_N], ptot[2], idx[MAX_N];
vector<int> stars[MAX_N], trans[MAX_N][2], G[MAX_N][2];
pii st[20][MAX_N];
ll sum, dp[MAX_N][2];

struct BIT
{
	int upper;
	ll nodes[MAX_N];
	
	void initialize(int up) { upper = up; }
	
	inline int lowbit(int x) { return x & (-x); }
	
	void update(int x, int d)
	{
		for (; x <= upper; x += lowbit(x))
			nodes[x] += d;
	}
	
	ll query(int x, ll ret = 0)
	{
		for (; x; x -= lowbit(x))
			ret += nodes[x];
		return ret;
	}
	
} tr[2];

pii query(int l, int r)
{
	int d = log2_[r - l + 1];
	return max(st[d][l], st[d][r - (1 << d) + 1]);
}

void dfs(int idx, int u)
{
	lft[idx][u] = ++ptot[idx];
	for (int v : G[idx][u])
		dfs(idx, v);
	rig[idx][u] = ptot[idx];
}

void updateLft(int ql)
{
	ll &ans = dp[ql][0];
	ans = 0;
	int qr = ch[ql][1];
	ql++, qr--;
	if (ql > qr)
		return;
	int mx_val = query(ql, qr).first, mx_pos = query(ql, qr).second;
	ans += dp[mx_pos][0] + dp[mx_pos][1];
	while (mx_pos > ql && query(ql, mx_pos - 1).first == mx_val)
		mx_pos = query(ql, mx_pos - 1).second, ans += dp[mx_pos][1];
	for (int p : trans[ql - 1][0])
		if (Y[p] > mx_val)
		{
			ll acc = C[p];
			acc += tr[0].query(lft[0][X[p]]) - tr[0].query(lft[0][ql - 1]);
			acc += tr[1].query(lft[1][X[p]]) - tr[1].query(lft[1][qr + 1]);
			ans = max(ans, acc);
		}
	tr[1].update(lft[1][ql - 1], ans);
	tr[1].update(rig[1][ql - 1] + 1, -ans);
}

void updateRig(int qr)
{
	ll &ans = dp[qr][1];
	ans = 0;
	int ql = ch[qr][0];
	ql++, qr--;
	if (ql > qr)
		return;
	int mx_val = query(ql, qr).first, mx_pos = query(ql, qr).second;
	ans += dp[mx_pos][0] + dp[mx_pos][1];
	while (mx_pos > ql && query(ql, mx_pos - 1).first == mx_val)
		mx_pos = query(ql, mx_pos - 1).second, ans += dp[mx_pos][1];
	for (int p : trans[qr + 1][1])
		if (Y[p] > mx_val)
		{
			ll acc = C[p];
			acc += tr[0].query(lft[0][X[p]]) - tr[0].query(lft[0][ql - 1]);
			acc += tr[1].query(lft[1][X[p]]) - tr[1].query(lft[1][qr + 1]);
			ans = max(ans, acc);
		}
	tr[0].update(lft[0][qr + 1], ans);
	tr[0].update(rig[0][qr + 1] + 1, -ans);
}

int main()
{
	scanf("%d", &n), hi[0] = hi[n + 1] = n;
	for (int i = 1; i <= n; i++)
		scanf("%d", &hi[i]), st[0][i] = make_pair(hi[i], i);
	for (int i = 1; i < 20; i++)
		for (int j = 1; j + (1 << i) - 1 <= n; j++)
			st[i][j] = max(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
	for (int i = 2; i <= n; i++)
		log2_[i] = log2_[i >> 1] + 1;
	scanf("%d", &m);
	for (int i = 1; i <= m; i++)
		scanf("%d%d%d", &X[i], &Y[i], &C[i]), sum += C[i], stars[X[i]].push_back(i);
	
	// Cartisen Tree;
	tail = 1;
	for (int i = 1; i <= n + 1; i++)
	{
		while (tail && hi[i] > hi[q[tail]])
			tail--;
		for (int sid : stars[i])
		{
			int l = 1, r = tail, res = 1;
			while (l <= r)
			{
				int mid = (l + r) >> 1;
				if (hi[q[mid]] >= Y[sid])
					l = mid + 1, res = mid;
				else
					r = mid - 1;
			}
			trans[q[res]][0].push_back(sid);
		}
		ch[i][0] = q[tail], q[++tail] = i;
	}
	q[tail = 1] = n + 1;
	for (int i = n; i >= 0; i--)
	{
		while (tail && hi[i] > hi[q[tail]])
			tail--;
		for (int sid : stars[i])
		{
			int l = 1, r = tail, res = 1;
			while (l <= r)
			{
				int mid = (l + r) >> 1;
				if (hi[q[mid]] >= Y[sid])
					l = mid + 1, res = mid;
				else
					r = mid - 1;
			}
			trans[q[res]][1].push_back(sid);
		}
		ch[i][1] = q[tail], q[++tail] = i;
	}
	tr[0].initialize(n + 2), tr[1].initialize(n + 2);
	for (int i = 1; i <= n + 1; i++)
		G[0][ch[i][0]].push_back(i);
	for (int i = 0; i <= n; i++)
		G[1][ch[i][1]].push_back(i);
	dfs(0, 0), dfs(1, n + 1);
	for (int i = 0; i <= n + 1; i++)
		idx[i] = i;
	sort(idx, idx + n + 2, [](const int &rhs1, const int &rhs2) { return hi[rhs1] < hi[rhs2]; });
	for (int ptr = 0; ptr <= n + 1; ptr++)
	{
		int u = idx[ptr];
		if (u != n + 1)
			updateLft(u);
		if (u != 0)
			updateRig(u);
	}
	for (int i = 0; i != n + 1; i = ch[i][1])
		sum -= dp[i][0];
	printf("%lld\n", sum);
	return 0;
}
