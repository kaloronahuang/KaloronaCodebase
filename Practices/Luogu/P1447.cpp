// P1447.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAX_N = 101000;

ll phi[MAX_N], prime[MAX_N], n, m, tot;
bool vis[MAX_N];

int main()
{
    scanf("%lld%lld", &n, &m);
    if (n > m)
        swap(n, m);
    phi[1] = 1;
    for (int i = 2; i < MAX_N; i++)
    {
        if (!vis[i])
            phi[prime[++tot] = i] = i - 1;
        for (int j = 1; j <= tot && i * prime[j] < MAX_N; j++)
        {
            vis[i * prime[j]] = true;
            if (i % prime[j] == 0)
            {
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            }
            phi[i * prime[j]] = phi[i] * phi[prime[j]];
        }
    }
    for (int i = 1; i < MAX_N; i++)
        phi[i] += phi[i - 1];
    ll ans = 0;
    for (ll T = 1, gx; T <= n; T = gx + 1)
    {
        gx = min(n / (n / T), m / (m / T));
        ans += (phi[gx] - phi[T - 1]) * (n / T) * (m / T);
    }
    ans = 2 * ans - n * m;
    printf("%lld", ans);
    return 0;
}