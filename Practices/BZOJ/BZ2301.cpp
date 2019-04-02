// P2522.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAX_N = 60010;
int prime[MAX_N], tot, a, b, c, d, k, n, mu[MAX_N], sum[MAX_N];
bool vis[MAX_N];
template <typename _Tp>
inline _Tp read(_Tp &x)
{
    char c11 = getchar(), ob = 0;
    x = 0;
    while (c11 ^ '-' && !isdigit(c11))
        c11 = getchar();
    if (c11 == '-')
        c11 = getchar(), ob = 1;
    while (isdigit(c11))
        x = x * 10 + c11 - '0', c11 = getchar();
    if (ob)
        x = -x;
    return x;
}
ll query(ll a, ll b)
{
    int ans = 0;
    for (int T = 1, gx = 0; T <= min(a, b); T = gx + 1)
    {
        gx = min(a / (a / T), b / (b / T));
        ans += (sum[gx] - sum[T - 1]) * (1LL * a / (1LL * T * k)) * (1LL * b / (1LL * T * k));
    }
    return ans;
}
int main()
{
    scanf("%d", &n);
    mu[1] = 1;
    for (int i = 2; i < MAX_N; i++)
    {
        if (!vis[i])
            prime[++tot] = i, mu[i] = -1;
        for (int j = 1; j <= tot && prime[j] * i < MAX_N; j++)
        {
            vis[i * prime[j]] = true;
            if (i % prime[j] == 0)
                break;
            else
                mu[i * prime[j]] = -mu[i];
        }
    }
    for (int i = 1; i < MAX_N; i++)
        sum[i] = sum[i - 1] + mu[i];
    while (n--)
    {
        read(a), read(b), read(c), read(d), read(k);
        printf("%lld\n", query(b, d) - query(a - 1, d) - query(b, c - 1) + query(a - 1, c - 1));
    }
    return 0;
}