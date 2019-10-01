// COGS167.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 1e5 + 200;

int seq[MAX_N], n, m;

bool judge(ll mid)
{
    ll prefix = 0, blocks = 0;
    for (int i = 1; i <= n; i++)
    {
        if (seq[i] > mid)
            return false;
        if (prefix + seq[i] > mid)
            blocks++, prefix = 0;
        prefix += seq[i];
    }
    blocks++;
    return blocks <= m;
}

int main()
{
    
    freopen("expense.in", "r", stdin);
    freopen("expense.out", "w", stdout);
    
    ll l = 0, r = 0, ans = 0;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &seq[i]), r += seq[i], l = max(1LL * seq[i], l);
    while (l <= r)
    {
        ll mid = (l + r) >> 1;
        if (judge(mid))
            r = mid - 1, ans = mid;
        else
            l = mid + 1;
    }
    printf("%lld", ans);
    return 0;
}