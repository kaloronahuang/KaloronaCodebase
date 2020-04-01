// P3534.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 1e6 + 200;

int n;
ll m, xi[MAX_N], ai[MAX_N], pre[MAX_N], prefix[MAX_N], suffix[MAX_N];

int check(int mid)
{
    ai[1] = xi[1];
    for (int i = 2; i <= n; i++)
        ai[i] = min(ai[i - 1] + mid, xi[i]);
    for (int i = n - 1; i >= 1; i--)
        ai[i] = min(ai[i + 1] + mid, ai[i]);
    ll acc = 0;
    for (int i = 1; i <= n; i++)
        acc += xi[i] - ai[i], pre[i] = pre[i - 1] + ai[i];
    if (acc > m)
        return 0;
    for (int i = 1, ptr = 1; i <= n; i++)
    {
        while (ptr < i && ai[ptr] <= 1LL * (i - ptr) * mid)
            ptr++;
        prefix[i] = pre[i - 1] - pre[ptr - 1] - 1LL * (i - ptr) * (i - ptr + 1) / 2 * mid;
    }
    for (int i = n, ptr = n; i >= 1; i--)
    {
        while (ptr > i && ai[ptr] <= 1LL * (ptr - i) * mid)
            ptr--;
        suffix[i] = pre[ptr] - pre[i] - 1LL * (ptr - i) * (ptr - i + 1) / 2 * mid;
    }
    for (int i = 1; i <= n; i++)
        if (prefix[i] + suffix[i] + acc + ai[i] <= m)
            return i;
    return 0;
}

int main()
{
    scanf("%d%lld", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &xi[i]);
    int l = 0, r = 1e9, res = 0;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (check(mid))
            r = mid - 1, res = mid;
        else
            l = mid + 1;
    }
    printf("%d %d\n", check(res), res);
    return 0;
}