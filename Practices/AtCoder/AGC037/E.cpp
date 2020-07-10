// E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, k;
char S[MAX_N], T[MAX_N], ans[MAX_N], minc = 'z', maxc = 'a';

void check(char *str, int idx)
{
	int ptr = n, len = 0;
	while (ptr >= 1 && str[ptr] == minc)
		ptr--, len++;
	while (idx != 0 && len < n)
		len <<= 1, idx--;
	if (len >= n)
	{
		fill(ans + 1, ans + 1 + n, minc);
		printf("%s\n", ans + 1), exit(0);
	}
	for (int i = 1; i <= len; i++)
		T[i] = minc;
	for (int i = len + 1; i <= n; i++)
		T[i] = str[ptr--];
	// compare;
	for (int i = 1; i <= n; i++)
		if (ans[i] < T[i])
			break;
		else if (ans[i] > T[i])
		{
			for (int j = 1; j <= n; j++)
				ans[j] = T[j];
			break;
		}
}		

int main()
{
	scanf("%d%d%s", &n, &k, S + 1);
	for (int i = 1; i <= n; i++)
	{
		minc = min(minc, S[i]), maxc = max(maxc, S[i]);
		ans[i] = 'z', S[(n << 1) - i + 1] = S[i];
	}
	if (minc == maxc)
		return printf("%s\n", ans + 1), 0;
	if (S[n] == minc)
		check(S, k);
	for (int i = n; i <= (n << 1); i++)
		if (S[i] == minc)
			check(S + i - n, k - 1);
	printf("%s\n", ans + 1);
	return 0;
}
