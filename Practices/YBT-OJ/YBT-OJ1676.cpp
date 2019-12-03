// YBT-OJ1676.cpp
#include <bits/stdc++.h>
#define ll long long
#define pr pair<ll, ll>

using namespace std;

const int MAX_N = 5e4 + 200;

int n, k;
ll mi[MAX_N];

bool check(ll mid)
{
    queue<pr> q;
    ll pow2sum = 0, prodsum = 0, siz = 0, usage = 0;
    for (int i = n; i >= 1; i--)
    {
        while (!q.empty() && mid <= 1LL * (q.front().first - i) * (q.front().first - i))
            siz -= q.front().second, pow2sum -= 1LL * q.front().second * q.front().first * q.front().first, prodsum -= 1LL * q.front().first * q.front().second, q.pop();
        ll curt = mi[i] - (1LL * siz * mid - (1LL * siz * i * i - 2LL * i * prodsum + pow2sum));
        if (curt >= 0)
        {
            ll req = (curt / mid) + 1;
            siz += req;
            q.push(make_pair(i, req)), pow2sum += 1LL * req * i * i, prodsum += 1LL * req * i, usage += req;
        }
    }
    return usage <= k;
}

int main()
{
    ll l = 0, r = 4e9, ans = r;
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &mi[i]);
    while (l <= r)
    {
        ll mid = (l + r) >> 1;
        if (check(mid))
            r = mid - 1, ans = mid;
        else
            l = mid + 1;
    }
    printf("%lld\n", ans);
    return 0;
}