// POJ2559.cpp
#include <iostream>
#include <stack>
#include <cstdio>
#define ll long long
using namespace std;
const int maxn = 100200;
ll n, num, wid[maxn], h[maxn], st[maxn];

int main()
{
    while (scanf("%lld", &n) != EOF && n != 0)
    {
        ll ans = 0;
        int p = 0;
        for (int i = 1; i <= n; i++)
            scanf("%lld", &h[i]);
        h[n + 1] = 0;
        for (int i = 1; i <= n + 1; i++)
            if (h[i] > st[p])
                st[++p] = h[i], wid[p] = 1;
            else
            {
                ll width = 0;
                while (st[p] > h[i])
                    width += wid[p], ans = max(ans, width * st[p--]);
                st[++p] = h[i], wid[p] = width + 1;
            }
        printf("%lld\n", ans);
    }
    return 0;
}