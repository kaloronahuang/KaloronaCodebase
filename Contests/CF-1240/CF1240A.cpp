// CF1240A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;
typedef long long ll;

int q, n, pi[MAX_N], A, B, xp, yp, mp[MAX_N];
ll k;

bool check(int len)
{
    for (int i = 1; i <= len; i++)
        mp[i] = ((i % A == 0) * xp) + ((i % B == 0) * yp);
    sort(mp + 1, mp + 1 + len), reverse(mp + 1, mp + 1 + len);
    ll pans = 0;
    for (int i = 1; i <= len; i++)
        pans += 1LL * mp[i] * pi[i] / 100;
    return pans >= k;
}

int main()
{
    scanf("%d", &q);
    while (q--)
    {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            scanf("%d", &pi[i]);
        sort(pi + 1, pi + 1 + n), reverse(pi + 1, pi + 1 + n);
        scanf("%d%d%d%d%lld", &xp, &A, &yp, &B, &k);
        int l = 1, r = n, res = -1;
        while (l <= r)
        {
            int mid = (l + r) >> 1;
            if (check(mid))
                r = mid - 1, res = mid;
            else
                l = mid + 1;
        }
        printf("%d\n", res);
    }
    return 0;
}
