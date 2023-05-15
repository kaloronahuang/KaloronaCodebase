// BezoutTheorum.cpp
#include <bits/stdc++.h>

using namespace std;

int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

int main()
{
	int n, d;
	scanf("%d%d", &n, &d), d = abs(d);
	for (int i = 2, val; i <= n; i++)
		scanf("%d", &val), d = gcd(d, abs(val));
	printf("%d\n", d);
	return 0;
}
