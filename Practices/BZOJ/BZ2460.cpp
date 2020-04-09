// BZ2460.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, ll> pil;

const int MAX_N = 1010;

int n;
pil tups[MAX_N];
ll ans, base[100];

ll insert(ll x)
{
    for (int i = 60; i >= 0; i--)
    {
        if (!(x & (1LL << i)))
            continue;
        if (base[i] == 0)
        {
            base[i] = x;
            break;
        }
        x ^= base[i];
    }
    return x;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld%d", &tups[i].second, &tups[i].first);
    sort(tups + 1, tups + 1 + n, [](const pil &rhs1, const pil &rhs2) { return rhs1.first > rhs2.first; });
    for (int i = 1; i <= n; i++)
        if (insert(tups[i].second))
            ans += tups[i].first;
    printf("%lld\n", ans);
    return 0;
}