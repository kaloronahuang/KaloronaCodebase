// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_K = 27, mod = 1e9 + 7;

int dp[MAX_K], n, m, k, prev_pos[MAX_K], ans;

int main()
{
    scanf("%d %d\n", &m, &k);
    int ans = 1, x, old;
    char ch;
    while (true)
    {
        ch = getchar(), x = ch - 'a' + 1;
        if (x < 1 || x > 26)
            break;
        old = ans;
        ans = 2LL * ans % mod, ans = (1LL * ans + mod - dp[x]) % mod;
        dp[x] = old, prev_pos[x] = ++n;
    }
    for (int i = 1; i <= m; i++)
    {
        x = 0;
        for (int j = 1; j <= k; j++)
            if (!x || prev_pos[x] > prev_pos[j])
                x = j;
        prev_pos[x] = ++n, old = ans;
        ans = 2LL * ans % mod, ans = (ans + mod - dp[x]) % mod;
        dp[x] = old;
    }
    printf("%d", ans);
    return 0;
}