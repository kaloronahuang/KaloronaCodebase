// B.cpp
// require C++ 11;
// --req-c++11
#include <bits/stdc++.h>
#define pr pair<int, int>
#define ll long long
using namespace std;
ll n, m, arr[20], arr1[20], ans = 0x3f3f3f3f;
pair<int, int> rules[70];
unordered_map<ll, ll> mp1, mp2;
ll gen(ll *ar)
{
    ll ans = 0;
    for (int i = n; i >= 1; i--)
        ans <<= 4, ans |= ar[i];
    return ans;
}
int main()
{
    scanf("%lld%lld", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &arr[i]), arr1[i] = i;
    for (int i = 1; i <= m; i++)
        scanf("%lld%lld", &rules[i].first, &rules[i].second);
    queue<ll> aq, bq;
    aq.push(gen(arr)), bq.push(gen(arr1));
    if (gen(arr) == gen(arr1))
        puts(0), exit(0);
    mp1[gen(arr)] = 0, mp2[gen(arr1)] = 0;
    while (!aq.empty() && !bq.empty())
    {
        ll stat = aq.front(), step = mp1[stat];
        if (step > ans)
            continue;
        aq.pop();
        for (int i = 1; i <= m; i++)
        {
            ll stat1 = stat;
            ll x = rules[i].first, y = rules[i].second, cod = (1 << 4) - 1;
            ll xcode = (stat1 >> ((x - 1) << 2)) & cod, ycode = (stat1 >> ((y - 1) << 2)) & cod;
            stat1 ^= (xcode << ((x - 1) << 2)), stat1 ^= (ycode << ((y - 1) << 2));
            stat1 |= (ycode << ((x - 1) << 2)), stat1 |= (xcode << ((y - 1) << 2));
            if (mp1.count(stat1) != 0)
                continue;
            if (mp2.count(stat1) != 0)
            {
                printf("%lld", mp2[stat1] + step + 1);
                return 0;
            }
            mp1[stat1] = step + 1;
            aq.push(stat1);
        }
        stat = bq.front(), step = mp2[stat];
        bq.pop();
        for (int i = 1; i <= m; i++)
        {
            ll stat1 = stat;
            ll x = rules[i].first, y = rules[i].second, cod = (1 << 4) - 1;
            ll xcode = (stat1 >> ((x - 1) << 2)) & cod, ycode = (stat1 >> ((y - 1) << 2)) & cod;
            stat1 ^= (xcode << ((x - 1) << 2)), stat1 ^= (ycode << ((y - 1) << 2));
            stat1 |= (ycode << ((x - 1) << 2)), stat1 |= (xcode << ((y - 1) << 2));
            if (mp2.count(stat1) != 0)
                continue;
            if (mp1.count(stat1) != 0)
            {
                printf("%lld", mp1[stat1] + step + 1);
                return 0;
            }
            mp2[stat1] = step + 1;
            bq.push(stat1);
        }
    }
    printf("%lld", ans);
    return 0;
}