// P3846.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll p, a, b;
ll quick_power(ll base, ll tim)
{
    ll tmp = 1;
    while (tim)
    {
        if (tim & 1)
            tmp = tmp * base % p;
        base = base * base % p;
        tim >>= 1;
    }
    return tmp;
}
map<ll, ll> hashTable;
int main()
{
    scanf("%lld%lld%lld", &p, &a, &b);
    a %= p;
    if (a == 0)
    {
        if (b == 0)
            printf("0");
        else
            printf("no solution");
        return 0;
    }
    hashTable.clear();
    ll m = ceil(sqrt(p));
    for (int j = 0, x = 1; j <= m; j++, x = x * a % p)
        hashTable[x * b % p] = j;
    ll unit = quick_power(a, m);
    for (int i = 1, x = unit; i <= m; i++, x = x * unit % p)
        if (hashTable.count(x))
        {
            printf("%lld", i * m - hashTable[x]);
            return 0;
        }
    printf("no solution");
    return 0;
}