// HDU-2516.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 101010;

ll arr[MAX_N], siz = 2, num;

int main()
{
	arr[1] = arr[2] = 1;
	while(arr[siz] <= (1LL << 32))
		arr[++siz] = arr[siz - 1] + arr[siz - 2];
	while(scanf("%d", &num) && num != 0)
	{
		if(*(lower_bound(arr+1, arr+1+siz, num)) == num)
			printf("Second win\n");
		else
			printf("First win\n");
	}
	return 0;
}
