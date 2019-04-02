// P2257.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAX_N = 10001000;
int T, miu[MAX_N], prime[MAX_N], cnt, prefix[MAX_N], sum[MAX_N];
bool flag[MAX_N];
void sieve()
{
    miu[1] = 1;
    for (int i = 2; i < MAX_N; i++)
    {
        if (!flag[i])
            prime[++cnt] = i, miu[i] = -1;
        for (int j = 1; j <= cnt && i * prime[j] < MAX_N; j++)
        {
            flag[i * prime[j]] = true;
            if (i % prime[j] == 0)
                break;
            miu[i * prime[j]] = -miu[i];
        }
    }
    for (int i = 1; i <= cnt; i++)
        for (int j = 1; prime[i] * j < MAX_N; j++)
            prefix[j * prime[i]] += miu[j];
    for (int i = 1; i < MAX_N; i++)
        sum[i] = sum[i - 1] + prefix[i];
}
ll solve(int a, int b)
{
    ll ans = 0;
    if (a > b)
        swap(a, b);
    for (int l = 1, r = 0; l <= a; l = r + 1)
    {
        r = min(a / (a / l), b / (b / l));
        ans += (ll)(sum[r] - sum[l - 1]) * (ll)(a / l) * (ll)(b / l);
    }
    return ans;
}
int main()
{
    sieve();
    scanf("%d", &T);
    while (T--)
    {
        int n, m;
        scanf("%d%d", &n, &m);
        if (n > m)
            swap(n, m);
        printf("%lld\n", solve(n, m));
    }
    return 0;
}