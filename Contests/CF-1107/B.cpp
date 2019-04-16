// B.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        ll ki, xi;
        scanf("%lld%lld", &ki, &xi);
        printf("%lld\n", (ki - 1) * 9 + xi);
    }
    return 0;
}