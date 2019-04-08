// P1403.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main()
{
    ll n, ans = 0;
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++)
        ans += n / i;
    printf("%lld", ans);
    return 0;
}