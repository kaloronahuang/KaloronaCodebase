// B.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

ll n, pows[20];

int main()
{
    scanf("%lld", &n);
    pows[0] = 1;
    for (int i = 1; i <= 18; i++)
        pows[i] = pows[i - 1] * 10;
    for (int stat = 0; stat < (1 << 19); stat++)
    {
        // to analyze;
        ll status = 0;
        for (int i = 0; i < 19; i++)
            if ((stat >> i) & 1)
                status += pows[i] * 1LL;
        if (status > n && status % n == 0)
            printf("%lld", status / n), exit(0);
    }
    printf("no solution");
    return 0;
}