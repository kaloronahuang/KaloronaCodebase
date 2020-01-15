// FOJ3822.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1000100;

int n, ai[MAX_N], prefix[MAX_N];

int main()
{
    long long ans = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]), prefix[i] = prefix[i - 1] + ai[i], ans += (ai[i] == 0) * prefix[i];
    printf("%lld\n", ans);
    return 0;
}