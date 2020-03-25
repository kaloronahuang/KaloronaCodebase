// ARC100B.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 2e5 + 200;

int n, ai[MAX_N];
ll pre[MAX_N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]), pre[i] = pre[i - 1] + ai[i];
    ll ans = 1e18;
    int lptr = 1, rptr = 3;
    for (int i = 2; i <= n - 2; i++)
    {
        while (lptr + 1 < i && abs((pre[i] - pre[lptr]) - pre[lptr]) >= abs((pre[i] - pre[lptr + 1]) - pre[lptr + 1]))
            lptr++;
        while (rptr + 1 < n && abs(pre[n] - pre[rptr] - (pre[rptr] - pre[i])) >= abs(pre[n] - pre[rptr + 1] - (pre[rptr + 1] - pre[i])))
            rptr++;
        ll part1 = pre[lptr], part2 = pre[i] - pre[lptr], part3 = pre[rptr] - pre[i], part4 = pre[n] - pre[rptr];
        ans = min(ans, max(abs(part1 - part2), max(abs(part1 - part3), max(abs(part1 - part4), max(abs(part2 - part3), max(abs(part2 - part4), abs(part3 - part4)))))));
    }
    printf("%lld\n", ans);
    return 0;
}