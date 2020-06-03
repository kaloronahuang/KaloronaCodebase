// LOJ6060.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

typedef long long ll;

int n, tot;
ll ai[MAX_N], tb[MAX_N], bi[MAX_N];

void insert(ll x)
{
    for (int i = 1; i <= tot; i++)
        if (x & (1LL << tb[i]))
        {
            if (bi[i] == 0)
            {
                bi[i] = x;
                break;
            }
            x ^= bi[i];
        }
}

int main()
{
    scanf("%d", &n);
    ll xorsum = 0;
    for (int i = 1; i <= n; i++)
        scanf("%lld", &ai[i]), xorsum ^= ai[i];
    for (int i = 62; i >= 0; i--)
        if (!(xorsum & (1LL << i)))
            tb[++tot] = i;
    for (int i = 62; i >= 0; i--)
        if (xorsum & (1LL << i))
            tb[++tot] = i;
    for (int i = 1; i <= n; i++)
        insert(ai[i]);
    ll x2 = 0;
    for (int i = 1; i <= tot; i++)
        if (!(x2 & (1LL << tb[i])))
            x2 ^= bi[i];
    printf("%lld\n", xorsum ^ x2);
    return 0;
}