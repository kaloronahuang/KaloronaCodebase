// ARC091B.cpp
#include <bits/stdc++.h>

using namespace std;

int n, k;

int main()
{
    scanf("%d%d", &n, &k);
    long long ans = 0;
    for (int b = max(k + 1, 1); b <= n; b++)
    {
        int rem = (n + 1) % b, loop_num = (n + 1) / b;
        int bpart = b - k;
        long long pans = 1LL * loop_num * bpart + max(0, rem - k) - (k == 0);
        ans += pans;
    }
    printf("%lld\n", ans);
    return 0;
}