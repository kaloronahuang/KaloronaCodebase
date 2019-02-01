// play.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAX_N = 14, mod = 998244353;
ll n, t, arr[MAX_N], ans = 0;
// going up;
void dfsup(ll pos, ll remain)
{
    if (pos == n + 1)
        return;
    if (remain == 0)
    {
        ans++, ans %= mod;
        return;
    }
    for (int i = pos + 1; i <= n; i++)
        if (arr[i] > arr[pos])
            dfsup(i, remain - 1);
}
void dfsdown(ll pos, ll remain)
{
    if (pos == n + 1)
        return;
    if (remain == 0)
    {
        ans++, ans %= mod;
        return;
    }
    for (int i = pos + 1; i <= n; i++)
        if (arr[i] < arr[pos])
            dfsdown(i, remain - 1);
}
void dfsb(ll pos, ll remain, ll limit)
{
    if (remain == 0)
    {
        ans++, ans %= mod;
        return;
    }
    if (remain == 2)
    {
        for (int i = pos + 1; i <= n; i++)
            if (arr[i] > arr[pos])
                dfsb(i, remain - 1, arr[pos]);
    }
    else if (remain == 1)
        for (int i = pos + 1; i <= n; i++)
            if (arr[i] < arr[pos] && arr[i] > limit)
                dfsb(i, remain - 1, arr[pos]);
}
void dfsc(ll pos, ll remain, ll limit)
{
    if (remain == 0)
    {
        ans++, ans %= mod;
        return;
    }
    if (remain == 2)
    {
        for (int i = pos + 1; i <= n; i++)
            if (arr[i] < arr[pos])
                dfsc(i, remain - 1, arr[pos]);
    }
    else if (remain == 1)
        for (int i = pos + 1; i <= n; i++)
            if (arr[i] > arr[pos] && arr[i] < limit)
                dfsc(i, remain - 1, arr[pos]);
}

int main()
{
    freopen("play.in", "r", stdin);
    freopen("play.out", "w", stdout);
    scanf("%d%d", &n, &t);
    for (int i = 1; i <= n; i++)
        scanf("%d", &arr[i]);
    ans += n;
    if (t % 3 == 0)
    {
        switch ((t / 3) % 3)
        {
        case 0:
            for (int i = 1; i <= n; i++)
                dfsup(1, 2);
            break;
        case 1:
            for (int i = 1; i <= n; i++)
                dfsb(1, 2, mod);
            break;
        case 2:
            for (int i = 1; i <= n; i++)
                dfsc(1, 2, mod);
            break;
        }
    }
    if (t % 2 == 0)
    {
        switch ((t / 2) % 2)
        {
        case 0:
            for (int i = 1; i <= n; i++)
                dfsup(1, 1);
            break;
        case 1:
            for (int i = 1; i <= n; i++)
                dfsdown(1, 1);
            break;
        }
    }
    printf("%d", ans % mod);
    return 0;
}