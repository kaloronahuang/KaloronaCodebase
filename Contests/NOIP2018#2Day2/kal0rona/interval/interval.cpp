// interval.cpp
#include <iostream>
#include <cstdio>

using namespace std;

const int maxn = 4000090;
#define ll long long
ll arr[maxn];
ll dp[maxn];
ll lengths[maxn];
ll stpos[maxn];
ll n;

ll gcd(ll a, ll b)
{
    if (a < b)
        return gcd(b, a);
    return (b == 0) ? a : gcd(b, a % b);
}

ll read()
{
    ll x = 0, f = 1;
    char c = getchar();
    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-')
            f = -1;
    for (; c >= '0' && c <= '9'; c = getchar())
        x = (x << 3) + (x << 1) + c - '0';
    return x * f;
}

int ans = 1;

void genDP()
{
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
        {
            bool flag1 = false;
            int last = arr[i];
            for (int k = i; k <= j; k++)
                if (flag1 = ((last = gcd(last, arr[k])) == 1))
                    break;
            if (flag1)
                break;
            else
                for (int k = i; k <= j; k++)
                    if (arr[k] == last)
                    {
                        ans = max(j - i + 1, ans);
                        break;
                    }
        }
}

int main()
{
    freopen("interval.in", "r", stdin);
    freopen("interval.out", "w", stdout);
    cin >> n;
    bool flag = false;
    for (int i = 1; i <= n; i++)
    {
        arr[i] = read();
        if (arr[i] == 1)
            flag = true;
    }
    if (flag)
    {
        cout << n;
        return 0;
    }
    genDP();
    cout << ans;
    return 0;
}