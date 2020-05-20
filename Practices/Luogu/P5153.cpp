// P5153.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200, mod = 1e9 + 7;

typedef long long ll;

ll n, lcm[MAX_N], cnt[MAX_N];
int f[MAX_N];

int fpow(int bas, ll tim)
{
    int ret = 1;
    while (tim)
    {
        if (tim & 1)
            ret = 1LL * ret * bas % mod;
        bas = 1LL * bas * bas % mod;
        tim >>= 1;
    }
    return ret;
}

int main()
{
    scanf("%lld", &n), f[2] = 1;
    for (int i = 3; i <= 50; i++)
        for (int j = 1; j <= i; j++)
            if (i % j != 0)
            {
                f[i] = f[j] + 1;
                break;
            }
    lcm[0] = 1;
    int pos = 1;
    for (int i = 1; i <= 50; i++)
    {
        lcm[i] = 1LL * lcm[i - 1] / __gcd(lcm[i - 1], 1LL * i) * i;
        if (lcm[i] > n)
        {
            pos = i;
            break;
        }
    }
    for (int i = 2; i <= pos; i++)
        cnt[f[i] + 1] += (n / lcm[i - 1] - pos / lcm[i - 1]) - (n / lcm[i] - pos / lcm[i]);
    for (int i = 2; i <= pos; i++)
        cnt[f[i]]++;
    int ret = 1;
    for (int i = 2; i <= 5; i++)
        ret = 1LL * ret * fpow(i, cnt[i]) % mod;
    printf("%d\n", ret);
    return 0;
}