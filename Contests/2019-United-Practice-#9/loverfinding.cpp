// loverfinding.cpp
#include <bits/stdc++.h>
#define ll long long
#define pr pair<ll, ll>

using namespace std;

const int MAX_N = 1001000;

ll n, sx, sy, tx, ty;

struct hash
{
	struct edge
	{
		pr val;
		int nxt;
	} edges[MAX_N];

	int head[MAX_N], current;

	int size() { return current; }

	void insert(pr curt)
	{
		ll hval = (abs(curt.first) * 131 + abs(curt.second)) % MAX_N;
		for (int i = head[hval]; i != -1; i = edges[i].nxt)
			if (edges[i].val == curt)
				return;
		edges[current].val = curt, edges[current].nxt = head[hval];
		head[hval] = current++;
	}
} st;

int main()
{

	freopen("loverfinding.in", "r", stdin);
	freopen("loverfinding.out", "w", stdout);

	memset(st.head, -1, sizeof(st.head));
	scanf("%lld%lld%lld%lld%lld", &n, &sx, &sy, &tx, &ty);
	if (sx == tx && sy == ty)
		puts("1"), exit(0);
	st.insert(make_pair(sx, sy));
	for (int i = 1; i <= n; i++)
	{
		ll dx, dy;
		scanf("%lld%lld", &dx, &dy);
		sx += dx, sy += dy;
		st.insert(make_pair(sx, sy));
		if (sx == tx && sy == ty)
			printf("%d", st.size()), exit(0);
	}
	puts("SingleDogMZX");
	return 0;
}
