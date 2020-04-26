// A.cpp
#include <bits/stdc++.h>

using namespace std;

int T, a, b, x, y;

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d%d%d", &x, &y, &a, &b);
        printf("%lld\n", min(1LL * a * x + 1LL * a * y, 1LL * min(x, y) * b + 1LL * (max(x, y) - min(x, y)) * a));
    }
    return 0;
}