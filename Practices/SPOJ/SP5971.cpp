// SP5971.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 1e6 + 200;

int T, n, phi[MAX_N], primes[MAX_N], tot;
ll func[MAX_N];

int main()
{
    phi[1] = 1;
    for (int i = 2; i < MAX_N; i++)
    {
        if (phi[i] == 0)
            phi[i] = i - 1, primes[++tot] = i;
        for (int j = 1; j <= tot && 1LL * i * primes[j] < MAX_N; j++)
        {
            if (i % primes[j] == 0)
            {
                phi[i * primes[j]] = phi[i] * primes[j];
                break;
            }
            phi[i * primes[j]] = phi[i] * phi[primes[j]];
        }
    }
    for (int i = 1; i < MAX_N; i++)
        for (int j = i; j < MAX_N; j += i)
            func[j] += (1LL * phi[j / i] * (j / i) + 1) >> 1;
    scanf("%d", &T);
    while (T--)
        scanf("%d", &n), printf("%lld\n", 1LL * func[n] * n);
    return 0;
}