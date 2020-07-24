// C.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 1e5 + 200;

int n, X, bi[MAX_N], li[MAX_N], ri[MAX_N], idx[MAX_N];
ll si[MAX_N];

ll calc(int id, int x)
{
    if (x <= bi[id])
        return 1LL * li[id] * x;
    return 1LL * li[id] * bi[id] + 1LL * ri[id] * (x - bi[id]);
}

ll check(ll mid)
{
    ll ans = 0, acc = 0;
    int spare = mid % X;
    if (spare == 0)
        spare += X;
    int cnt = (mid - spare) / X;
    for (int i = 1; i <= cnt; i++)
        acc += si[idx[i]];
    for (int i = cnt + 1; i <= n; i++)
        ans = max(ans, acc + calc(idx[i], spare));
    acc += si[idx[cnt + 1]];
    for (int i = 1; i <= cnt; i++)
        ans = max(ans, acc - si[idx[i]] + calc(idx[i], spare));
    return ans;
}

int main()
{
    ll goal = 0;
    scanf("%d%d", &n, &X);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d%d", &bi[i], &li[i], &ri[i]);
        si[i] = calc(i, X), goal += 1LL * bi[i] * li[i], idx[i] = i;
    }
    sort(idx + 1, idx + 1 + n, [](const int &rhs1, const int &rhs2) { return si[rhs1] > si[rhs2]; });
    if (goal == 0)
        puts("0"), exit(0);
    ll l = 1, r = 1LL * n * X, res;
    while (l <= r)
    {
        ll mid = (l + r) >> 1;
        if (check(mid) >= goal)
            r = mid - 1, res = mid;
        else
            l = mid + 1;
    }
    printf("%lld\n", res);
    return 0;
}