// ARC096A.cpp
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int A, B, C, X, Y;
    long long ans = 0;
    scanf("%d%d%d%d%d", &A, &B, &C, &X, &Y);
    if (A + B >= 2LL * C)
    {
        int d = min(X, Y);
        ans += 2LL * d * C, X -= d, Y -= d;
    }
    if (X > 0)
    {
        if (A > 2LL * C)
            ans += 2LL * X * C;
        else
            ans += X * A;
        X = 0;
    }
    if (Y > 0)
    {
        if (B > 2LL * C)
            ans += 2LL * Y * C;
        else
            ans += Y * B;
        Y = 0;
    }

    printf("%lld\n", ans);
    return 0;
}