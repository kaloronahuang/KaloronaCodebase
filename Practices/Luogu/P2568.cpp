// P2568.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 1e7 + 200;

ll n, phi[MAX_N], tot, prime[MAX_N];
bool vis[MAX_N];

int main()
{
    scanf("%lld", &n);
    phi[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        if (!vis[i])
            prime[++tot] = i, phi[i] = i - 1;
        for (int j = 1; j <= tot && 1LL * i * prime[j] <= n; j++)
        {
            vis[i * prime[j]] = true;
            if (i % prime[j] == 0)
            {
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            }
            else
                phi[i * prime[j]] = phi[i] * phi[prime[j]];
        }
    }
    for (int i = 1; i <= n; i++)
        phi[i] += phi[i - 1];

    ll ret = 0;
    for (int i = 1; i <= tot; i++)
        ret += (phi[n / prime[i]] * 2) - 1;
    printf("%lld", ret);
    return 0;
}