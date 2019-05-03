// LOJ3096.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAX_N = 1e6 + 2000;
ll p, q, n, m, t, ai[MAX_N], bi[MAX_N], sum[MAX_N], tot[MAX_N], len, ans;
int key[MAX_N], rk[MAX_N];
bool vis[MAX_N];

ll gcd(ll x, ll y) { return y == 0 ? x : gcd(y, x % y); }

int main()
{
    scanf("%lld%lld%lld%lld%lld", &p, &q, &n, &m, &t);
    len = q / gcd(p, q);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &ai[i]);
    for (int i = 1; i <= m; i++)
    {
        scanf("%lld", &bi[i]), sum[bi[i]]++;
        key[bi[i]] = 1;
    }
    for (int i = 0; i < q; i++)
    {
        if (vis[i])
            continue;
        vis[i] = true;
        int now, last = i;
        rk[i] = 1;
        for (now = (last + p) % q; now != i; last = now, now = (now + p) % q)
            rk[now] = rk[last] + 1, sum[now] += sum[last], vis[now] = true;
        tot[i] = sum[last];
        for (int j = (i + p) % q; j != i; j = (j + p) % q)
            tot[j] = sum[last];
    }
    for (int i = 1; i <= n; i++)
    {
        if (ai[i] >= t)
            continue;
        ll cnt = (t - 1 - ai[i]) / p;
        ll A = ai[i] % q, B = (A + cnt % len * p) % q;
        ans += cnt / len * tot[A];
        if (rk[A] <= rk[B])
            ans += sum[B] - sum[A] + key[A];
        else
            ans += tot[A] - (sum[A] - sum[B] - key[A]);
    }
    printf("%lld", ans);
    return 0;
}