// ARC091C.cpp
#include <bits/stdc++.h>

using namespace std;

int n, a, b;

int main()
{
    scanf("%d%d%d", &n, &a, &b);
    if (a + b - 1 > n || 1LL * a * b < n)
        puts("-1"), exit(0);
    while (n > 0)
    {
        int rd = min(a, n - b + 1);
        for (int i = n - rd + 1; i <= n; i++)
            printf("%d ", i);
        n -= rd, b--;
    }
    puts("");
    return 0;
}