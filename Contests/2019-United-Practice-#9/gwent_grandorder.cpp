// gwent_grandorder.cpp
// WDNMD
#include <bits/stdc++.h>

/*
#define ll long long
using namespace std;

const int MAX_N = 1e5 + 200;

struct card
{
	int val, typ, pos, force, effectPos;
	bool spy;
	bool operator<(const card& cd) const { return val < cd.val; }
	bool operator<=(const card& cd) const { return val <= cd.val; }
} mine;

struct board
{
	card st[4][MAX_N];
	int cnts[4];
	ll fcst[4];
} enemy;

int n, m, k, ans1, ans2;

int main()
{
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1, tmp; i <= m; i++)
	{
		card u;
		scanf("%d%d", &u.val, &u.typ);
		scanf("%d%d%d", &u.pos, &u.force, &tmp);
		u.spy = (tmp == 1);
		enemy.st[u.pos][++enemy.cnts[u.pos]] = u;
	}
	// calculate the force;
	
	for (int i = 1; i <= 3; i++)
	{
		for (int j = 1; j <= enemy.cnts[i]; j++)
			enemy.fcst[i] += enemy.st[i][j].force;
		ans1 = max(ans1, enemy.fcst[i]);
	}
	for (int i = 1, tmp; i <= n; i++)
	{
		card u;
		scanf("%d%d", &u.val, &u.typ);
		scanf("%d%d%d", &u.pos, &u.force, &tmp);
		u.spy = (tmp == 1);
		mine[i] = u;
	}
	return 0;
}

*/

int main() 
{ 
	freopen("gwent_grandorder.in", "r", stdin);
	freopen("gwent_grandorder.out", "w", stdout);
	printf("SingleDogMZX");
	return 0;
}
