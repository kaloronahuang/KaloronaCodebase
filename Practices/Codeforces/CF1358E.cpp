// CF1358E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e5 + 200;

typedef long long ll;

int n;
ll ai[MAX_N], x, pre[MAX_N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= (n + 1) >> 1; i++)
        scanf("%lld", &ai[i]), pre[i] = pre[i - 1] + ai[i];
    scanf("%lld", &x);
    ll res = 1e18;
    for (int i = 1; i <= (n + 1) >> 1; i++)
    {
        ll curt = 1LL * x * (n >> 1) + pre[(n + 1) >> 1] - pre[i - 1];
        if (res == 1e18)
            res = curt;
        else
            res = (res - x) < curt ? res - x : curt;
        if (res > 0)
            printf("%d\n", n - i + 1), exit(0);
    }
    puts("-1");
    return 0;
}