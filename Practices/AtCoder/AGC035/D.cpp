// D.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MAX_N = 20, INF = 0x3f3f3f3f3f3f3f3f;

int n;
ll ai[MAX_N];

ll solve(int l, int r, ll cL, ll cR)
{
    if (l + 1 > r - 1)
        return 0;
    ll ret = INF;
    for (int i = l + 1; i <= r - 1; i++)
        ret = min(ret, solve(l, i, cL + cR, cR) + solve(i, r, cL, cL + cR) + 1LL * (cL + cR) * ai[i]);
    return ret;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &ai[i]);
    printf("%lld\n", solve(1, n, 1, 1) + ai[1] + ai[n]);
    return 0;
}