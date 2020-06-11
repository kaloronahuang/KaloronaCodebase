// CF665E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = (1e6 + 200) * 30;

int n, k, seq[MAX_N], ch[MAX_N][2], siz[MAX_N], ptot = 1;
long long ans;

void insert(int x)
{
	int p = 1;
	for (int i = 30; i >= 0; i--)
	{
		int b = (x >> i) & 1;
		if (ch[p][b] == 0)
			ch[p][b] = ++ptot;
		p = ch[p][b];
	}
	siz[p]++;
}

int query(int threshold)
{
	int p = 1, ret = 0;
	for (int i = 30; i >= 0; i--)
	{
		int b = (threshold >> i) & 1;
		int kb = (k >> i) & 1;
		if (kb == 0)
			ret += siz[ch[p][b ^ 1]];
		p = ch[p][kb ^ b]; //, printf("%d", kb ^ b);
		if (p == 0)
			break;
	}
	ret += siz[p];
	// puts("");
	return ret;
}

void dfs(int u)
{
	for (int i = 0; i < 2; i++)
		if (ch[u][i])
			dfs(ch[u][i]), siz[u] += siz[ch[u][i]];
}

int main()
{
	scanf("%d%d", &n, &k), insert(0);
	for (int i = 1; i <= n; i++)
		scanf("%d", &seq[i]), seq[i] ^= seq[i - 1], insert(seq[i]);
	dfs(1);
	for (int i = 0; i <= n; i++)
		ans += query(seq[i]); //, printf("SHT %d\n", query(seq[i]));
	printf("%lld\n", ans >> 1);
	return 0;
}
