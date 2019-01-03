// P1069.cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <map>
#define ll long long
#define pr pair<ll, ll>
using namespace std;
const int MX_N = 10020, M_M = 30020, INF = 0x3f3f3f3f;
ll n, m1, m2, s[MX_N], k;
bool isPrime[M_M];
map<ll, ll> getFactors(ll num, ll par)
{
    map<ll, ll> vec;
    ll pre = num, limit = sqrt(num);
    for (int i = 2; i <= limit; i++)
        if (isPrime[i])
        {
            for (k = 0; num > 0 && num % i == 0; num /= i, k++)
                ;
            if (k != 0)
                vec[i] = k * par;
            num = pre;
        }
    return vec;
}
int main()
{
    scanf("%lld%lld%lld", &n, &m1, &m2);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &s[i]);
    memset(isPrime, true, sizeof(isPrime));
    isPrime[1] = false;
    for (int i = 2; i < M_M; i++)
        if (isPrime[i])
            for (int k = 2; i * k < M_M; k++)
                isPrime[i * k] = false;
    ll id = -1, tim = INF;
    map<ll, ll> pre = getFactors(m1, m2);
    for (int i = 1; i <= n; i++)
    {
        map<ll, ll> now = getFactors(s[i], 1);
        ll ti = -1;
        bool flag = false;
        for (std::map<ll, ll>::iterator it = now.begin(); it != now.end(); it++)
        {
            ll key = it->first, val = it->second;
            if (pre.count(key) == 0)
            {
                flag = true;
                break;
            }
            if (pre[key] % val == 0)
            {
                if (ti == -1)
                    ti = pre[key] / val;
                else if (ti != pre[key] / val)
                {
                    flag = true;
                    break;
                }
            }
            else
            {
                flag = true;
                break;
            }
        }
        if (flag)
            continue;
        else if (ti < tim)
            tim = ti, id = i;
    }
    if (id == -1)
        printf("%lld", (ll)-1);
    else
        printf("%lld", tim);
    return 0;
}