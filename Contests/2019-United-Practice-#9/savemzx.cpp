// savemzx.cpp
#include <bits/stdc++.h>
#define ull unsigned long long
#define ll long long

using namespace std;

const int MAX_N = 5050;
const ull bitnum = 133;

int n, head[MAX_N], current;
ull pre[MAX_N], pows[MAX_N];
ll ans;
char str[MAX_N];

struct edge
{
	int to, nxt;
	ll weight;
} edges[MAX_N << 1];

void addpath(int src, int dst, ll weight)
{
	edges[current].to = dst, edges[current].nxt = head[src];
	edges[current].weight = weight, head[src] = current++;
}

ull getHash(int l, int r)
{
	return pre[r] - pre[l - 1] * (pows[r - l + 1]);
}

ll dfs(int u)
{
	ll longest = 0, second_longest = 0;
	for (int i = head[u]; i != -1; i = edges[i].nxt)
	{
		ll dist = dfs(edges[i].to) + edges[i].weight;
		if (dist >= longest)
			swap(longest, second_longest), longest = dist;
		else if (dist > second_longest)
			second_longest = dist;
	}
	if (second_longest != 0)
		ans = max(longest + second_longest, ans);
	return longest;
}

int main()
{
	freopen("savemzx.in", "r", stdin);
	freopen("savemzx.out", "w", stdout);
	memset(head, -1, sizeof(head));
	scanf("%s", str + 1), n = strlen(str + 1);
	for (int i = pows[0] = 1; i <= n; i++)
		pows[i] = pows[i - 1] * bitnum, pre[i] = pre[i - 1] * bitnum + str[i] - 'a';
	for (int i = 1; i <= n; i++)
	{
		// prefix str[1...i];
		if (i == 1)
		{
			addpath(0, i, 1);
			continue;
		}
		int pos = 0;
		for (int j = 1; j <= i - 1; j++)
		{
			// prefix : [1...j]
			// suffix : [i - j + 1, i]
			if (getHash(1, j) == getHash(i - j + 1, i))
				pos = j;
		}
		addpath(pos, i, (i - pos) * (i - pos));
	}
	dfs(0), printf("%lld", ans);
	return 0;
}
