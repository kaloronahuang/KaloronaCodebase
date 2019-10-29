// A.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 1e5 + 200;

ll prefix[MAX_N], T, n;

int getHighest(ll bas)
{
    for (int i = 63; i >= 0; i--)
        if (bas & (1LL << i))
            return i + 1;
    return 0;
}

int check(ll x)
{
    int cnt = getHighest(x);
    ll forehalf = x >> (cnt >> 1), prod = 0;
    for (int i = 0; i < (cnt >> 1); i++)
        if ((forehalf & (1LL << i)) == 0)
            prod |= 1LL << ((cnt >> 1) - i - 1);
    return x >= ((forehalf << (cnt >> 1)) | prod);
}

int main()
{
    scanf("%lld", &T);
    while (T--)
    {
        scanf("%lld", &n);
        int cnt = getHighest(n);
        if (cnt & 1)
            printf("%lld\n", (1LL << (cnt >> 1)) - 1);
        else
            printf("%lld\n", ((n ^ (1LL << (cnt - 1))) >> (cnt >> 1)) + check(n) + (1LL << ((cnt - 1) >> 1)) - 1);
    }
    return 0;
}