// CH3201.cpp
#include <bits/stdc++.h>
using namespace std;
int n, a0, a1, b0, b1;
int gcd(int a, int b) { return (b == 0) ? a : gcd(b, a % b); }
int main()
{
    scanf("%d", &n);
    while (n--)
    {
        int ans = 0;
        scanf("%d%d%d%d", &a0, &a1, &b0, &b1);
        int p = b1 / b0, q = a0 / a1;
        for (int x = 1; x * x <= b1; x++)
            if (b1 % x == 0)
            {
                if (x % a1 == 0 && gcd(p, b1 / x) == 1 && gcd(q, x / a1) == 1)
                    ans++;
                int y = b1 / x;
                if (x == y)
                    continue;
                if (y % a1 == 0 && gcd(p, b1 / y) == 1 && gcd(q, y / a1) == 1)
                    ans++;
            }
        printf("%d\n", ans);
    }
    return 0;
}