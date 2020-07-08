// CF542D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

typedef long long ll;
typedef pair<int, ll> pil;

ll n, dp[2][10010];
int primes[MAX_N], tot, dtot, ptot, ktot;
bool vis[MAX_N];
vector<ll> divisors;
map<ll, int> divId, pkind;
pil tups[MAX_N];

void sieve()
{
    for (int i = 2; i < MAX_N; i++)
    {
        if (!vis[i])
            primes[++tot] = i;
        for (int j = 1; j <= tot && 1LL * i * primes[j] < MAX_N; j++)
        {
            vis[i * primes[j]] = true;
            if (i % primes[j] == 0)
                break;
        }
    }
}

int main()
{
    scanf("%lld", &n), sieve();
    for (int i = 1; 1LL * i * i <= n; i++)
        if (n % i == 0)
        {
            divisors.push_back(i);
            if (n / i != i)
                divisors.push_back(n / i);
        }
    dtot = divisors.size();
    divisors.push_back(0), sort(divisors.begin(), divisors.end());
    for (int i = 1; i <= dtot; i++)
        divId[divisors[i]] = i;
    for (ll pc : divisors)
        if (pc > 2)
        {
            ll x = pc - 1, pbase = -1;
            bool flag = true;
            for (int i = 1; i <= tot && 1LL * primes[i] * primes[i] <= x; i++)
                if (x % primes[i] == 0)
                {
                    while (x % primes[i] == 0)
                        x /= primes[i];
                    if (x == 1)
                        pbase = primes[i];
                    else
                        flag = false;
                    break;
                }
            if (flag && x > 1)
                pbase = x;
            if (pbase != -1 && flag)
            {
                if (pkind.count(pbase) == 0)
                    pkind[pbase] = ++ktot;
                tups[++ptot] = make_pair(pkind[pbase], pc);
            }
        }
    sort(tups + 1, tups + 1 + ptot);
    dp[0][1] = 1;
    int b = 0;
    for (int typ = 1; typ <= ptot; typ++)
    {
        if (tups[typ].first != tups[typ - 1].first)
            b ^= 1, memcpy(dp[b], dp[b ^ 1], sizeof(dp[b]));
        for (int i = 1; i <= dtot; i++)
            if (divisors[i] % tups[typ].second == 0)
                dp[b][i] += dp[b ^ 1][divId[divisors[i] / tups[typ].second]];
    }
    printf("%lld\n", dp[b][dtot]);
    return 0;
}