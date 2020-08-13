//这是本题的special judge
//在编译后可以在终端内通过调用 spj <input-file> <output-file> <standard-output-file> 来得到你的得分
#include "testlib.h"
#include <bits/stdc++.h>
#define ll long long
#define maxn 100005
#define mod 998244353
#define db double
#define vi vector<int>
#define pb push_back
#define mp make_pair
#define pi pair<int, int>
#define fi first
#define se second
using namespace std;
map<pi, int> fl;
int jud[15];
int main(int argc, char **argv)
{
	registerTestlibCmd(argc, argv);
	int n, m;
	n = inf.readInt(), m = inf.readInt();
	for (int i = 1; i <= 10; i++)
		jud[i] = inf.readInt(1, n);
	for (int j = 0; j < m; j++)
	{
		int u, v;
		u = inf.readInt();
		v = inf.readInt();
		fl[mp(u, v)] = 1;
	}
	vi re(n + 1);
	vi cur(n);
	for (int i = 1; i <= n; i++)
		re[i] = 0;
	int len = ouf.readInt();
	for (int i = 0; i < len; i++)
		cur[i] = ouf.readInt(1, n);
	int vali = 1;
	for (int i = 0; i < len - 1; i++)
		if (!fl[mp(cur[i], cur[i + 1])])
			vali = 0;
	if (vali)
	{
		for (int i = 0; i < len; i++)
		{
			if (re[cur[i]])
				vali = 0;
			re[cur[i]] = 1;
		}
	}
	if (vali)
	{
		int pnt = 0;
		for (int i = 1; i <= 10; i++)
			if (len >= jud[i])
				pnt = i;
		if (pnt == 10)
			quitf(_ok, "Correct!Your answer's length=%d", len);
		else
			quitp((double)pnt / 10, "Correct!Your answer's length=%d", len);
	}
	else
		quitp(0.0, "Invalid Path.");
}
