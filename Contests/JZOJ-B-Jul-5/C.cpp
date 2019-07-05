// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2000000;

int ai[MAX_N], bi[MAX_N], T, n, k;

int main()
{
	scanf("%d", &T);
	
	for (int cas = 1; cas <= T; cas++)
	{
		scanf("%d%d", &n, &k);
		int i = 0, j = 0;
		ai[0] = bi[0] = 1;
		while (ai[i] < n)
		{
			i++;
			ai[i] = bi[i-1]+1;
			while(ai[j + 1] * k < ai[i])
				j++;
			if(ai[j]* k < ai[i])
				bi[i] = bi[j] + ai[i];
			else
				bi[i] = ai[i];
		}
		printf("Case %d: ", cas);
		if (ai[i] == n)
			printf("lose\n");
		else
		{
			int ans = 0;
			while (n != 0)
			{
				if(n >= ai[i])
					n -= ai[i], ans = ai[i];
				i--;
			}
			printf("%d\n", ans);
		}
	}
	return 0;
}
