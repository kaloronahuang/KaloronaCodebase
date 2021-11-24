// I.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e6 + 200;

typedef long long ll;

int n;
ll ai[MAX_N], q[MAX_N], pre[MAX_N], mgr[MAX_N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &ai[i]);
    for (int i = 1; i <= n; i++)
        if (i & 1)
            pre[i] = pre[i - 1] + ai[i];
        else
            pre[i] = pre[i - 1] - ai[i];
    int tail = 1;
    ll ans = 0;
    for (int i = 2; i <= n; i += 2)
    {
        ll pt = pre[i], pos = pre[i - 1];
        while (tail > 0 && q[tail] > pt)
            ans += pos - q[tail] + mgr[tail], pos = q[tail], mgr[tail] = 0, tail--;
        if (tail > 0)
            ans += pos - pt;
        if (tail > 0 && q[tail] == pt)
            ans += mgr[tail], mgr[tail]++;
        else
            q[++tail] = pt, mgr[tail] = (tail > 1 && q[tail] > q[tail - 1]);
    }
    printf("%lld\n", ans);
    return 0;
}