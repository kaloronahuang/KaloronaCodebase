// P1069.cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#define ll long long
using namespace std;
const int MX_N = 30020, INF = 0x3f3f3f3f;
ll n, m1, m2, arr[MX_N], pipePrime[MX_N], cellPrime[MX_N], lit, ans = INF;
int main()
{
    scanf("%lld%lld%lld", &n, &m1, &m2);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &arr[i]);
    if (m1 == 1)
    {
        printf("0");
        return 0;
    }
    for (int i = 2; m1 != 1; i++)
    {
        while (!(m1 % i))
            m1 /= i, pipePrime[i] += m2;
        lit = max(lit, (ll)i);
    }
    for (int i = 1; i <= n; i++)
    {
        ll now = 0;
        for (int j = 2; j <= lit; j++)
            if (pipePrime[j] != 0)
            {
                ll tim = 0;
                while (!(arr[i] % j))
                    arr[i] /= j, tim++;
                if (!tim)
                {
                    now = INF;
                    break;
                }
                now = max(now, (pipePrime[j] - 1) / tim);
            }
        ans = min(ans, now);
    }
    if (ans != INF)
        printf("%lld", ans + 1);
    else
        printf("-1");
    return 0;
}