// D.cpp
#include <bits/stdc++.h>

using namespace std;

int n, ai[40];

int main()
{
    scanf("%d", &n);
    for (int i = 1, x; i <= n; i++)
    {
        scanf("%d", &x);
        for (int i = 19; i >= 0; i--)
            if (x & (1 << i))
                ai[i]++;
    }
    long long ans = 0;
    for (int i = 1; i <= n; i++)
    {
        int x = 0;
        for (int i = 19; i >= 0; i--)
            if (ai[i])
                x |= (1 << i), ai[i]--;
        ans += 1LL * x * x;
    }
    printf("%lld\n", ans);
    return 0;
}