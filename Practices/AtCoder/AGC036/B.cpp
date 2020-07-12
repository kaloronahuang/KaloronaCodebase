// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200, LOG = 60;

int n, ai[MAX_N], mem[MAX_N], nxt[MAX_N], up[LOG][MAX_N], ansBox[MAX_N];
long long k;

int main()
{
	scanf("%d%lld", &n, &k);
	for (int i = 1; i <= n; i++)
		scanf("%d", &ai[i]);
	for (int i = n; i >= 1; i--)
		mem[ai[i]] = i;
	for (int i = n; i >= 1; i--)
		nxt[i] = mem[ai[i]], mem[ai[i]] = i;
	up[0][0] = 1;
	for (int i = n; i >= 1; i--)
		if (nxt[i] <= i)
			if (nxt[i] == n)
				up[0][i] = 0;
			else
				up[0][i] = nxt[i] + 1;
		else if (nxt[i] == n)
			up[0][i] = 1;
		else
			up[0][i] = up[0][nxt[i] + 1];
	for (int i = 1; i < LOG; i++)
		for (int j = 0; j <= n; j++)
			up[i][j] = up[i - 1][up[i - 1][j]];
	int ans = 0;
	for (int i = LOG - 1; i >= 0; i--)
		if (k & (1LL << i))
			ans = up[i][ans];
	memset(mem, 0, sizeof(mem));
	int tot = 0;
	if (ans == 0)
		return 0;
	for (int i = ans; i <= n; i++)
	{
		if (mem[ai[i]] == 0)
			ansBox[++tot] = ai[i], mem[ai[i]] = tot;
		else
		{
			int pos = mem[ai[i]];
			while (tot >= pos)
				mem[ansBox[tot--]] = 0;
		}
	}
	for (int i = 1; i <= tot; i++)
		printf("%d ", ansBox[i]);
	puts("");
	return 0;
}
