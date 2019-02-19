// BZ2818.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAX_N = 10000005;
ll n, phi[MAX_N];
bool isPrime[MAX_N];
int main()
{
    //memset(isPrime, true, sizeof(isPrime));
    scanf("%lld", &n);
    for (int i = 2; i <= n; i++)
        phi[i] = i;
    for (int i = 2; i <= n; i++)
        if (!isPrime[i])
            for (int j = i; j <= n; j += i)
            {
                if (j != i)
                    isPrime[j] = true;
                phi[j] = phi[j] / i * (i - 1);
            }
    phi[1] = 1;
    for (int i = 2; i <= n; i++)
        phi[i] += phi[i - 1];
    long long ans = 0;
    for (int i = 2; i <= n; i++)
        if (!isPrime[i])
            ans += 2 * phi[n / i] - 1;
    printf("%lld", ans);
    return 0;
}