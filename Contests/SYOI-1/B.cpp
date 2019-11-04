// B.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 1010;

ll di[MAX_N], T;

int main()
{
    freopen("lmyjr.in", "r", stdin);
    freopen("lmyjr.out", "w", stdout);
    for (int i = 1; i < MAX_N; i++)
        di[i] = di[i - 1] + i;
    scanf("%lld", &T);
    while (T--)
    {
        ll x, y;
        scanf("%lld%lld", &x, &y);
        ll num = di[y] + 1LL * (x - 1) * di[y - 1];
        printf("%lld ", num);
        ll mi_pos = 0x3f3f3f3f, mx_pos = 0;
        if (num == 1)
        {
            printf("%lld %lld\n", 1LL, x);
            continue;
        }
        for (int i = 2; i < MAX_N; i++)
        {
            if (num < di[i])
                break;
            ll delta = num - di[i];
            if (delta % di[i - 1] == 0)
                mi_pos = min(mi_pos, delta / di[i - 1]), mx_pos = max(mx_pos, delta / di[i - 1]);
        }
        printf("%lld %lld\n", mi_pos + 1, mx_pos + 1);
    }
    return 0;
}