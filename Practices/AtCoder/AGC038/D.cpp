// D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, m, q, mem[MAX_N], siz[MAX_N];

struct clue
{
	int a, b, c;
} clues[MAX_N];

int find(int x) { return mem[x] == x ? x : mem[x] = find(mem[x]); }

int main()
{
	scanf("%d%d%d", &n, &m, &q);
	for (int i = 1; i <= n; i++)
		mem[i] = i;
	for (int i = 1; i <= q; i++)
	{
		scanf("%d%d%d", &clues[i].a, &clues[i].b, &clues[i].c);
		clues[i].a++, clues[i].b++;
		if (clues[i].c == 0 && find(clues[i].a) != find(clues[i].b))
			mem[find(clues[i].a)] = find(clues[i].b);
	}
	int component = 0, c1 = 0;
	for (int i = 1; i <= n; i++)
		component += find(i) == i;
	for (int i = 1; i <= q; i++)
		if (clues[i].c == 1)
		{
			c1++;
			int u = find(clues[i].a), v = find(clues[i].b);
			if (u == v)
				puts("No"), exit(0);
		}
	long long lft = c1 ? max(3, component) : component - 1, rig = 1LL * component * (component - 1) / 2;
	puts((lft <= m - (n - component) && m - (n - component) <= rig) ? "Yes" : "No");
	return 0;
}
