// A.cpp
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int MAX_N = 3e6 + 200;

int cnt[MAX_N], n;
ll ans;

int main()
{
    scanf("%d", &n);
    for (int i = 1, tmp; i <= n; i++)
        scanf("%d", &tmp), cnt[tmp]++;
    for (int i = 1, sum = 0; i <= int(2e6); i++, sum = 0)
    {
        for (int j = 1; 1LL * i * j <= int(2e6); j++)
            sum += cnt[1LL * i * j];
        if (sum >= 2)
            ans = max(ans, 1LL * sum * i);
    }
    printf("%lld", ans);
    return 0;
}