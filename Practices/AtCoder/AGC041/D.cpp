// D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5050;

int n, mod, dp[MAX_N], coeff[MAX_N];

int main()
{
    scanf("%d%d", &n, &mod), dp[0] = 1;
    for (int i = 1; i < n; i++)
        for (int j = min(n - i + 1, i), k = j; j < n; j++)
            dp[j] = (0LL + dp[j] + dp[j - k]) % mod;
    int ans = 0;
    for (int i = 0; i < n; i++)
        ans = (0LL + ans + 1LL * dp[i] * (n - i) % mod) % mod;
    printf("%d\n", ans);
    return 0;
}