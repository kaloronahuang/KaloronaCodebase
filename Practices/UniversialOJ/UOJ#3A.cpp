// UOJ#3A.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }

const int MAX_N = 1e6 + 200;

ll n, ai[MAX_N], primes[MAX_N];

int main()
{
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &ai[i]);
    for (int i = 1; 1LL * i * i <= ai[1]; i++)
        if (ai[1] % i == 0)
        {
            primes[++primes[0]] = i;
            if (ai[1] / i != i)
                primes[++primes[0]] = ai[1] / i;
        }
    sort(primes + 1, primes + 1 + primes[0]);
    for (int i = 1; i <= n; i++)
    {
        bool flag = true;
        ll di = gcd(ai[1], ai[i]);
        for (int j = 1; j <= primes[0]; j++)
            if (di % primes[j] == 0 && di / primes[j] < di)
            {
                printf("%lld ", di / primes[j]);
                flag = false;
                break;
            }
        if (flag)
            printf("-1 ");
    }
    return 0;
}