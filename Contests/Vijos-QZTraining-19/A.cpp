// A.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 100007;

int n, seq[MAX_N], hash[MAX_N], prime[MAX_N], tot, f[MAX_N];
ll cnt1[MAX_N], cnt2[MAX_N];
bool vis[MAX_N];

void sieve()
{
    for (int i = 2; i < MAX_N; i++)
    {
        if (!vis[i])
            prime[++tot] = i, f[i] = tot;
        for (int j = 1; j <= tot && 1LL * prime[j] * i < MAX_N; j++)
        {
            vis[i * prime[j]] = true, f[i * prime[j]] = j;
            if (i % prime[j] == 0)
                break;
        }
    }
}

bool check(ll mid)
{
    memset(cnt2, 0, sizeof(cnt2));
    for (int i = 1; i <= tot && prime[i] <= mid; i++)
    {
        ll tmp = mid;
        while (tmp)
            tmp /= prime[i], cnt2[i] += tmp;
    }
    for (int i = 1; i <= tot; i++)
        if (cnt1[i] > cnt2[i])
            return false;
    return true;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &seq[i]);
    sieve();
    for (int id = 1; id <= n; id++)
    {
        int tmp = seq[id];
        while (tmp != 1)
        {
            int last_prime = prime[f[tmp]];
            while (tmp % last_prime == 0)
                cnt1[f[tmp]]++, tmp /= last_prime;
        }
    }
    ll l = 2, r = 1e12, ans = 0;
    while (l <= r)
    {
        ll mid = (l + r) >> 1;
        if (check(mid))
            r = mid - 1, ans = mid;
        else
            l = mid + 1;
    }
    printf("%lld", ans);
    return 0;
}