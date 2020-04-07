// BZ1122.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2001000;

typedef long long ll;

int n, p, q, x, y, pre[MAX_N], head, dq[MAX_N], min_val[MAX_N], tail;
char str[MAX_N];

int main()
{
    scanf("%d%d%d%d%d%s", &n, &p, &q, &x, &y, str + 1);
    for (int i = 1; i <= n; i++)
        pre[i] = str[i] == '+' ? 1 : -1;
    for (int i = n + 1; i <= (n << 1); i++)
        pre[i] = pre[i - n];
    for (int i = n << 1; i >= 1; i--)
        pre[i] += pre[i + 1];
    head = 1, tail = 0;
    for (int i = n << 1; i >= 1; i--)
    {
        while (head <= tail && pre[dq[tail]] < pre[i])
            tail--;
        dq[++tail] = i;
        while (head <= tail && dq[head] - i > n)
            head++;
        if (i <= n)
            min_val[i] = pre[i] - pre[dq[head]];
    }
    int pos_num = (q - p - pre[n + 1]) >> 1;
    ll ans = 0x7fffffffffffffff;
    for (int i = 1; i <= n; i++)
    {
        ll cost = 1LL * (n - i + 1) % n * y + 1LL * abs(pos_num) * x;
        if (p + min_val[i] + (max(pos_num, 0) << 1) < 0)
            cost += ((0 - (p + min_val[i] + (max(pos_num, 0) << 1)) + 1) >> 1) * (x << 1);
        ans =  min(ans, cost);
    }
    printf("%lld\n", ans);
    return 0;
}