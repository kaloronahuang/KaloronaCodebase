// ARC074C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 330, mod = 1e9 + 7;

typedef pair<int, int> pii;

int n, m, dp[MAX_N][MAX_N][MAX_N], ans;
vector<pii> rig[MAX_N];

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1, l, r, x; i <= m; i++)
    {
        scanf("%d%d%d", &l, &r, &x);
        rig[r].push_back(make_pair(l, x));
    }
    dp[0][0][0] = 1;
    for (int a = 0; a <= n; a++)
        for (int b = 0; b <= n; b++)
            for (int c = 0; c <= n; c++)
            {
                if (dp[a][b][c] == 0 || (a == b && a != 0) || (b == c && b != 0) || (a == c && a != 0))
                    continue;
                int i = max(a, max(b, c));
                bool flag = true;
                for (pii stat : rig[i])
                    if ((a >= stat.first) + (b >= stat.first) + (c >= stat.first) != stat.second)
                    {
                        flag = false;
                        break;
                    }
                if (!flag)
                {
                    dp[a][b][c] = 0;
                    continue;
                }
                dp[i + 1][b][c] = (0LL + dp[i + 1][b][c] + dp[a][b][c]) % mod;
                dp[a][i + 1][c] = (0LL + dp[a][i + 1][c] + dp[a][b][c]) % mod;
                dp[a][b][i + 1] = (0LL + dp[a][b][i + 1] + dp[a][b][c]) % mod;
                if (i == n)
                    ans = (0LL + ans + dp[a][b][c]) % mod;
            }
    printf("%d\n", ans);
    return 0;
}