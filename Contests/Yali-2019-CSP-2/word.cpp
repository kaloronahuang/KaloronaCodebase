// word.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, zcnt;
char str[MAX_N];

int main()
{
	freopen("word.in", "r", stdin);
	freopen("word.out", "w", stdout);
	scanf("%d%s", &n, str + 1);
	for (int i = 1; i <= n; i++)
		zcnt += str[i] == 'z';
	printf("%d %d\n", zcnt, (n - (zcnt << 2)) / 3);
	return 0;
}
