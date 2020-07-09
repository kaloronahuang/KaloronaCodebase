// A.cpp
#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n, m, A, B;
	scanf("%d%d%d%d", &n, &m, &B, &A);
	for (int i = 1; i <= n; i++, puts(""))
		for (int j = 1; j <= m; j++)
			if ((i <= A) ^ (j <= B))
				printf("1");
			else
				printf("0");
	return 0;
}
