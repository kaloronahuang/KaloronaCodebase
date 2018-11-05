// interval.cpp
#include <iostream>
#include <cstdio>

using namespace std;

const int maxn = 4000090;
#define ll long long
ll arr[maxn];
ll n;

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

int ans = 0;

int main()
{
    n = read();
    for (int i = 1; i <= n; i++)
        arr[i] = read();
    for (int i = 1; i <= n; i++)
    {
        int l, r;
        l = r = i;
        while (arr[l - 1] % arr[i] == 0 && l > 1)
            l--;
        while (arr[r + 1] % arr[i] == 0 && r < n)
            r++;
        ans = max(ans, r - l + 1);
        i = r;
    }
    printf("%lld", ans);
    return 0;
}