// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e3 + 200;

char mp[MAX_N][MAX_N];
int n, m, T, delta[MAX_N][MAX_N], now[MAX_N][MAX_N], matrix[MAX_N][MAX_N];

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        memset(delta, 0, sizeof(delta)), memset(now, 0, sizeof(now));
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++)
            scanf("%s", mp[i] + 1);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                if (mp[i][j] == 'R')
                    matrix[i][j] = 1;
                else if (mp[i][j] == 'G')
                    matrix[i][j] = 2;
                else
                    matrix[i][j] = 0;
        int cnt = 0;
        for (int i = n; i >= 1; i--)
        {
            delta[i][m + 1] += delta[i + 1][m + 1];
            for (int j = m; j >= 1; j--)
            {
                delta[i][j] += delta[i + 1][j];
                now[i][j] = now[i][j + 1] + delta[i][j + 1];
                int curt = (matrix[i][j] + now[i][j]) % 3;
                cnt += (3 - curt) % 3;
                now[i][j] += (3 - curt) % 3, delta[i][j + 1] += (3 - curt) % 3;
            }
        }
        printf("%s\n", cnt % 3 == 2 ? "dreagonm" : (cnt % 3 == 1 ? "fengxunling" : "BLUESKY007"));
    }
    return 0;
}