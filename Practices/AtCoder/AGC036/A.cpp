// A.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll S;

int main()
{
	scanf("%lld", &S);
	ll y = (S + int(1e9) - 1) / int(1e9), x = y * int(1e9) - S;
	printf("%d %d %d %d %lld %lld\n", 0, 0, int(1e9), 1, x, y);
	return 0;
}
