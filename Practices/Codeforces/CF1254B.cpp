// CF1254B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

typedef long long ll;

int n, ai[MAX_N];
ll sum;
vector<ll> pbox;

ll solve(ll base)
{
    ll ret = 0, sum = 0;
    for (int i = 1; i <= n; i++)
    {
        sum = (0LL + sum + ai[i]) % base;
        ret += min(sum, base - sum);
    }
    return ret;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]), sum += ai[i];
    if (sum == 0)
        puts("0"), exit(0);
    if (sum == 1)
        puts("-1"), exit(0);
    ll acc = sum;
    for (int i = 2; 1LL * i * i <= acc; i++)
        if (acc % i == 0)
        {
            pbox.push_back(i);
            while (acc % i == 0)
                acc /= i;
        }
    if (acc > 1)
        pbox.push_back(acc);
    ll ans = 0x7fffffffffffffff;
    for (ll base : pbox)
        ans = min(ans, solve(base));
    printf("%lld\n", ans);
    return 0;
}