// lilac.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2520;

typedef long long ll;
typedef pair<int, int> pii;

int n, m, start_pos, mem[MAX_N], siz[MAX_N], org_mem[MAX_N], org_siz[MAX_N], parity[MAX_N], op[MAX_N], deg[MAX_N];
ll sum;
bool vis[MAX_N];
vector<pii> edges[MAX_N];

int find(int x) { return mem[x] == x ? x : mem[x] = find(mem[x]); }

void merge(int x, int y)
{
	x = find(x), y = find(y);
	if (x == y)
		return;
	if (siz[x] < siz[y])
		swap(x, y);
	mem[y] = x, siz[x] += siz[y];
}

ll solve(int end_pos)
{
	deg[end_pos]++;
	memset(vis, false, sizeof(vis)), memcpy(mem, org_mem, sizeof(mem));
	memcpy(siz, org_siz, sizeof(siz)), memcpy(parity, op, sizeof(op));
	for (int i = 0; i <= n; i++)
		edges[i].clear();
	ll ans = sum;
	parity[start_pos] ^= 1, parity[end_pos] ^= 1;
	int last_ptr = 0, tot = 0;
	for (int i = 1; i <= n; i++)
		if (parity[i] == 1)
			if (last_ptr)
			{
				for (int j = last_ptr; j < i; j++)
					ans++, merge(j, j + 1);
				last_ptr = 0;
			}
			else
				last_ptr = i;
	for (int i = 1; i <= n; i++)
		if (deg[i] && !vis[find(i)])
			vis[find(i)] = true, tot++;
	for (int i = 1, gx; i < n; i = gx)
	{
		gx = i + 1;
		if (deg[i] == 0)
			continue;
		while (gx <= n && deg[gx] == 0)
			gx++;
		if (deg[gx])
			edges[gx - i].push_back(make_pair(i, gx));
	}
	for (int i = 1; i < n && tot > 1; i++)
		for (pii x : edges[i])
			if (find(x.first) != find(x.second))
			{
				merge(x.first, x.second), tot--, ans += 2LL * i;
				if (tot == 1)
					break;
			}
	deg[end_pos]--;
	return ans;
}

int main()
{
	scanf("%d%d%d", &n, &m, &start_pos), deg[start_pos] = 1;
	for (int i = 1; i <= n; i++)
		mem[i] = i, siz[i] = 1;
	for (int i = 1, u, v; i <= m; i++)
	{
		scanf("%d%d", &u, &v), sum += abs(u - v);
		op[u] ^= 1, op[v] ^= 1, deg[u] = deg[v] = 1;
		merge(u, v);
	}
	memcpy(org_mem, mem, sizeof(mem)), memcpy(org_siz, siz, sizeof(siz));
	for (int end_pos = 1; end_pos <= n; end_pos++)
		printf("%lld ", solve(end_pos));
	puts("");
	return 0;
}