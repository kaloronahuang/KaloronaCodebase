// CF1365E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 550;

typedef long long ll;

int n;
ll ai[MAX_N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &ai[i]);
    ll ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            for (int k = 1; k <= n; k++)
                ans = max(ans, ai[i] | ai[j] | ai[k]);
    printf("%lld\n", ans);
    return 0;
}