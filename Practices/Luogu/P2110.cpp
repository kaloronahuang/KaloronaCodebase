// P2110.cpp
#include <iostream>
#include <cstdio>
#define ll long long
using namespace std;
ll L, R;
ll dp[20][20][20];

ll query(ll num)
{
    if (num <= 9)
        return num;
    ll sum = 9 + num / 10;
    ll inner = num % 10;
    ll highest = num;
    while (highest >= 10)
        highest /= 10;
    if (highest > inner)
        sum--;
    return sum;
}

int main()
{
    scanf("%lld%lld", &L, &R);
    printf("%lld", query(R) - query(L - 1));
    return 0;
}