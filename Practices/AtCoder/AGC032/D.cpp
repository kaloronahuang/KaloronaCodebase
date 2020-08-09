// D.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 5e3 + 200;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int n, A, B, pi[MAX_N], pos[MAX_N];
ll dp[MAX_N][MAX_N];

int main()
{
    scanf("%d%d%d", &n, &A, &B);
    for (int i = 1; i <= n; i++)
        scanf("%d", &pi[i]), pos[pi[i]] = i;
    memset(dp, 0x3f, sizeof(dp)), dp[0][0] = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < i; j++)
            if (dp[i - 1][j] != INF)
                if (pos[i] > pos[j])
                {
                    dp[i][i] = min(dp[i][i], dp[i - 1][j]);
                    dp[i][j] = min(dp[i][j], dp[i - 1][j] + B);
                }
                else
                    dp[i][j] = min(dp[i][j], dp[i - 1][j] + A);
    }
    printf("%lld\n", *min_element(dp[n], dp[n] + 1 + n));
    return 0;
}