// P4549.cpp
#include <bits/stdc++.h>

using namespace std;

int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

int main()
{
    int n, di;
    scanf("%d%d", &n, &di), di = abs(di);
    for (int i = 2, tmp; i <= n; i++)
        scanf("%d", &tmp), di = gcd(abs(tmp), di);
    printf("%d", di);
    return 0;
}