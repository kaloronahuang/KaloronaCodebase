// CF1190A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

typedef long long ll;

ll n, m, k, pi[MAX_N];

int main()
{
    scanf("%lld%lld%lld", &n, &m, &k);
    for (int i = 1; i <= m; i++)
        scanf("%lld", &pi[i]);
    int current_shift = 0, ans = 0;
    for (int i = 1, g; i <= m; i = g)
    {
        ll pos = (pi[i] - current_shift);
        g = i + 1;
        while (ll((pi[g] - current_shift - 1) / k) == ll((pos - 1) / k))
            g++;
        current_shift += g - i, ans++;
    }
    printf("%d\n", ans);
    return 0;
}