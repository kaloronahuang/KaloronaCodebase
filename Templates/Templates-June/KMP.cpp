// KMP.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

int n, m, nxt[MAX_N];
char S[MAX_N], T[MAX_N];

int main()
{
	scanf("%s%s", S + 1, T + 1);
	n = strlen(S + 1), m = strlen(T + 1);
	for (int i = 2; i <= m; i++)
	{
		int j = nxt[i - 1];
		while (j && T[j + 1] != T[i])
			j = nxt[j];
		if (T[j + 1] == T[i])
			nxt[i] = ++j;
		else
			nxt[i] = 0;
	}
	for (int i = 1, j = 1; i <= n; i++)
	{
		while (j && T[j + 1] != S[i])
			j = nxt[j];
		if (T[j + 1] == S[i])
		{
			j++;
			if (j == m)
				printf("%d\n", i - m + 1), j = nxt[j];
		}
	}
	for (int i = 1; i <= m; i++)
		printf("%d ", nxt[i]);
	return 0;
}
