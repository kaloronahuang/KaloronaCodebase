// P4213.cpp
#include <bits/stdc++.h>
#define reg register
#define ll long long
using namespace std;

const int MAX_N = 6e6 + 200;
unordered_map<int, ll> ump_phi, ump_mu;
ll phi[MAX_N], mu[MAX_N], prime[MAX_N], tot;
bool vis[MAX_N];

ll sieve_phi(int num)
{
    if (num < MAX_N)
        return phi[num];
    if (ump_phi.count(num))
        return ump_phi[num];
    ll ans = (unsigned long long)num * (num + 1) / 2;
    for (reg int i = 2, gx; i <= num; i = gx + 1)
    {
        gx = num / (num / i);
        ans -= (gx - i + 1) * sieve_phi(num / i);
    }
    return ump_phi[num] = ans;
}

ll sieve_mu(int num)
{
    if (num < MAX_N)
        return mu[num];
    if (ump_mu.count(num))
        return ump_mu[num];
    ll ans = 1;
    for (reg int i = 2, gx; i <= num; i = gx + 1)
    {
        gx = num / (num / i);
        ans -= (gx - i + 1) * sieve_mu(num / i);
    }
    return ump_mu[num] = ans;
}

void preprocess()
{
    tot = 0, phi[1] = mu[1] = 1;
    for (reg int i = 2; i < MAX_N; i++)
    {
        if (!vis[i])
            prime[++tot] = i, mu[i] = -1, phi[i] = i - 1;
        for (reg int j = 1; j <= tot && i * prime[j] < MAX_N; j++)
        {
            vis[i * prime[j]] = true;
            if (i % prime[j] == 0)
            {
                mu[prime[j] * i] = 0, phi[prime[j] * i] = prime[j] * phi[i];
                break;
            }
            phi[i * prime[j]] = phi[prime[j]] * phi[i];
            mu[i * prime[j]] = -mu[i];
        }
    }
    for (reg int i = 2; i < MAX_N; i++)
        phi[i] += phi[i - 1], mu[i] += mu[i - 1];
}

int main()
{
    int q;
    preprocess();
    scanf("%d", &q);
    while (q--)
    {
        ll num;
        scanf("%lld", &num);
        printf("%lld %lld\n", sieve_phi(num), sieve_mu(num));
    }
    return 0;
}