// A.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 21;
int n, wi[MAX_N];
long long ans1;
double pi[MAX_N], dp[(1 << 20)];
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lf%d", &pi[i], &wi[i]), ans1 += wi[i];
    for (int stat = 0; stat < (1 << n); stat++)
    {
        double psum = 0, ans = 0;
        for (int i = 1; i <= n; i++)
            if (stat & (1 << (i - 1)))
            {
                int prestat = stat ^ (1 << (i - 1));
                psum += pi[i];
                ans += pi[i] * dp[prestat];
            }
        if (psum != 0)
            dp[stat] = (ans + 1) / psum;
    }
    printf("%lld\n%.3lf", ans1, dp[(1 << n) - 1]);
    return 0;
}