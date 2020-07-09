// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int n, k, pi[MAX_N], max_val[20][MAX_N], min_val[20][MAX_N], log2_[MAX_N];
bool st[20][MAX_N];

bool query(int l, int r)
{
	bool ret = true;
	for (int i = 19; i >= 0; i--)
		if (l + (1 << i) - 1 <= r)
		{
			ret &= st[i][l] && (l + (1 << i) - 1 == r || pi[l + (1 << i) - 1] <= pi[l + (1 << i)]);
			l += (1 << i);
		}
	return ret;
}

int queryMin(int l, int r)
{
	int d = log2_[r - l + 1];
	return min(min_val[d][l], min_val[d][r - (1 << d) + 1]);
}

int queryMax(int l, int r)
{
	int d = log2_[r - l + 1];
	return max(max_val[d][l], max_val[d][r - (1 << d) + 1]);
}

int main()
{
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++)
		scanf("%d", &pi[i]), st[0][i] = true, max_val[0][i] = min_val[0][i] = pi[i];
	for (int i = 2; i <= n; i++)
		log2_[i] = log2_[i >> 1] + 1;
	for (int i = 1; i < 20; i++)
		for (int j = 1; j + (1 << i) - 1 <= n; j++)
		{
			st[i][j] = st[i - 1][j] && st[i - 1][j + (1 << (i - 1))] && (pi[j + (1 << (i - 1)) - 1] <= pi[j + (1 << (i - 1))]);
			min_val[i][j] = min(min_val[i - 1][j], min_val[i - 1][j + (1 << (i - 1))]);
			max_val[i][j] = max(max_val[i - 1][j], max_val[i - 1][j + (1 << (i - 1))]);
		}
	int pl = -1, pr = -1, ans = 0;
	bool flag = false;
	for (int i = 1; i + k - 1 <= n; i++)
		if (pl == -1)
			ans++, pl = i, pr = i + k - 1, flag |= query(pl, pr);
		else if (i <= pr)
		{
			bool verdict = query(pl, i - 1) && query(pr + 1, i + k - 1);
			verdict &= queryMax(pl, i - 1) <= queryMin(i, pr) && queryMax(i, pr) <= queryMin(pr + 1, i + k - 1);
			if (verdict)
				continue;
			else if (!(query(i, i + k - 1) && flag))
				ans++, pl = i, pr = i + k - 1, flag |= query(pl, pr);
		}
		else if (query(pl, pr) && query(i, i + k - 1))
			continue;
		else if (!(query(i, i + k - 1) && flag))
			ans++, pl = i, pr = i + k - 1, flag |= query(pl, pr);
	printf("%d\n", ans);
	return 0;
}
