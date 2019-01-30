// HDU-2138.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll bs[6] = {2, 3, 7, 61, 24251};
ll n, ans, tmp;
ll quick_pow(ll base, ll tim, ll p)
{
    ll tmp = 1;
    while (tim)
    {
        if (tim & 1)
            tmp = tmp * base % p;
        base = base * base % p;
        tim >>= 1;
    }
    return tmp;
}
bool isPrime(ll p)
{
    // 把 p - 1 设为我们需要的值形式
    ll x = p - 1, k = 0, j;
    while (!(x & 1))
        x >>= 1, k++;
    // 进行随机的素数测试，这是 Miller-Rabin 的核心部分
    for (int i = 0; i <= 4; i++)
    {
        // 用于减少常数的判断
        if (p == bs[i])
            return true;
        // 算出本身的基底以便后期运算
        ll r = quick_pow(bs[i], x, p);
        // 常数判断
        if (r == 1 || r == p - 1)
            continue;
        for (j = 1; j <= k; j++)
        {
            // 重点：
            // 在二次探查中，p - 1 = 2^(kx)，如果
            // 这个出现了意外解，那么 p 就是合数
            r = r * r % p;
            if (r == p - 1)
                break;
        }
        // 判断
        if (j > k)
            return false;
    }
    return true;
}
int main()
{
    while (scanf("%lld", &n) != EOF)
    {
        while (n--)
        {
            scanf("%lld", &tmp);
            if (isPrime(tmp))
                ans++;
        }
        printf("%lld\n", ans);
        ans = 0;
    }
    return 0;
}