// CF1355E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

typedef long long ll;

int n, A, R, M, hi[MAX_N];
ll S;

ll check(ll mid)
{
    ll cost = 0, above = 0, lower = 0;
    for (int i = 1; i <= n; i++)
        if (hi[i] > mid)
            above += hi[i] - mid;
        else
            lower += mid - hi[i];
    ll d = min(above, lower);
    above -= d, lower -= d;
    cost = 1LL * A * lower + 1LL * R * above + 1LL * d * min(0LL + A + R, 0LL + M);
    return cost;
}

int main()
{
    scanf("%d%d%d%d", &n, &A, &R, &M);
    for (int i = 1; i <= n; i++)
        scanf("%d", &hi[i]), S += hi[i];
    ll l = 0, r = 1e10, res;
    while (l <= r)
    {
        ll lmid = l + (r - l) / 3, rmid = r - (r - l) / 3;
        if (check(lmid) > check(rmid))
            l = lmid + 1, res = check(rmid);
        else
            r = rmid - 1, res = check(lmid);
    }
    printf("%lld\n", res);
    return 0;
}