// P3327.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAX_N = 50100;
int n, prime[MAX_N], tot, mu[MAX_N], muprefix[MAX_N];
ll g[MAX_N];
bool vis[MAX_N];
int main()
{
    scanf("%d", &n);
    mu[1] = 1;
    for (int i = 2; i < MAX_N; i++)
    {
        if (!vis[i])
            prime[++tot] = i, mu[i] = -1;
        for (int j = 1; j <= tot && i * prime[j] < MAX_N; j++)
        {
            vis[i * prime[j]] = true;
            if (i % prime[j] == 0)
                break;
            else
                mu[i * prime[j]] = -mu[i];
        }
    }
    for (int i = 1; i < MAX_N; i++)
        muprefix[i] = muprefix[i - 1] + mu[i];
    for (int i = 1; i < MAX_N; i++)
    {
        ll ans = 0;
        for (int l = 1, r = 0; l <= i; l = r + 1)
        {
            r = (i / (i / l));
            ans += 1LL * (r - l + 1) * 1LL * (i / l);
        }
        g[i] = ans;
    }
    while (n--)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        ll ans = 0;
        for (int l = 1, r; l <= min(a, b); l = r + 1)
        {
            r = min(a / (a / l), b / (b / l));
            ans += (muprefix[r] - muprefix[l - 1]) * 1LL * g[a / l] * 1LL * g[b / l];
        }
        printf("%lld\n", ans);
    }
    return 0;
}