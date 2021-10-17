// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

typedef long long ll;

int T, n;
ll ai[MAX_N], sum;

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n), sum = 0;
        for (int i = 1; i <= n; i++)
            scanf("%lld", &ai[i]), sum += ai[i], ai[i] *= n;
        map<ll, int> mp;
        ll ans = 0;
        for (int i = 1; i <= n; i++)
            ans += mp[(sum << 1) - ai[i]], mp[ai[i]]++;
        printf("%lld\n", ans);
    }
    return 0;
}