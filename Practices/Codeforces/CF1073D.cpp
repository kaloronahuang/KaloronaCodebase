// CF1073D.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 2e5 + 200;

ll n, ai[MAX_N], T, sum, cnt, ans;

int main()
{
    scanf("%lld%lld", &n, &T);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &ai[i]), sum += ai[i];
    while (sum > 0)
    {
        sum = 0, cnt = 0;
        for (int i = 1; i <= n; i++)
            if (sum + ai[i] <= T)
                sum += ai[i], cnt++;
        if (sum == 0)
            break;
        ans += cnt * (ll)(T / sum), T %= sum;
    }
    printf("%lld", ans);
    return 0;
}