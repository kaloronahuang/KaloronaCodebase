// POJ3904.cpp
//#include <bits/stdc++.h>
#include <cstdio>
#include <cstring>
#define ll long long
using namespace std;
const int MAX_N = 1e4 + 200;
ll C[MAX_N], prime[MAX_N], fact[MAX_N], sum[MAX_N], tot, n, tmpx;
void divide(ll num)
{
    tot = 0;
    for (ll i = 2; i * i <= num; i++)
        if (num % i == 0)
        {
            prime[tot++] = i;
            while (num % i == 0)
                num /= i;
        }
    if (num > 1)
        prime[tot++] = num;
    for (int i = 1; i < (1 << tot); i++)
    {
        ll tmp = 1, sm = 0;
        for (int j = 0; j < tot; j++)
            if ((i >> j) & 1)
                tmp *= prime[j], sm++;
        fact[tmp]++, sum[tmp] = sm;
    }
}
int main()
{
    // initialize the Choose Numbers;
    for (ll i = 4; i < MAX_N; i++)
        C[i] = i * (i - 1) * (i - 2) * (i - 3) / 24;
    while (scanf("%lld", &n) != EOF)
    {
        memset(fact, 0, sizeof(fact));
        for (int i = 1; i <= n; i++)
            scanf("%lld", &tmpx), divide(tmpx);
        ll part = 0;
        for (int i = 2; i < MAX_N; i++)
            if (fact[i] >= 4)
            {
                if (sum[i] & 1)
                    part += C[fact[i]];
                else
                    part -= C[fact[i]];
            }
        printf("%lld\n", (ll)(C[n] - part));
    }
    return 0;
}