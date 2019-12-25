// P4844.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 1e7;

ll n, m;
int prime[MAX_N], tot, mu[MAX_N], head[MAX_N], current;
bool vis[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void sieve(int top)
{
    mu[1] = 1;
    for (int i = 2; i <= m; i++)
    {
        if (!vis[i])
            prime[++tot] = i, mu[i] = -1;
        for (int j = 1; j <= tot && 1LL * i * prime[j] <= m; j++)
        {
            vis[i * prime[j]] = true;
            if (i % prime[j] == 0)
            {
                mu[i * prime[j]] = 0;
                break;
            }
            mu[i * prime[j]] = -mu[i];
        }
    }
}

ll calc(ll u, ll k)
{
    ll ret = 0;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
    {
        if (abs(edges[i].to) > k)
            break;
        ret += k / edges[i].to;
    }
    return ret;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%lld", &n), m = sqrt(n << 1), sieve(m);
    for (int i = 1; i <= m; i++)
        for (int j = 1; 1LL * i * j <= m; j++)
            if (mu[j])
                addpath(1LL * i * j, mu[j] * j);
    ll ans = 0;
    for (int i = 1; i <= m; i++)
        ans += calc(i, min(n / i, i - 1LL)) - calc(i, max(1LL, i - (n / i)) - 1LL);
    printf("%lld", ans);
    return 0;
}