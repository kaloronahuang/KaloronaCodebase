// P3082.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 10100, MAX_M = 1010;

int dp[2][MAX_M], n, m, nxt[MAX_M];
char strA[MAX_N], strB[MAX_M];

int main()
{
    scanf("%s%s", strA + 1, strB + 1);
    n = strlen(strA + 1), m = strlen(strB + 1);
    for (int i = 2, j = 0; i <= m; i++)
    {
        while (j != 0 && strB[j + 1] != strB[i])
            j = nxt[j];
        if (strB[j + 1] == strB[i])
            j++;
        nxt[i] = j;
    }
    memset(dp[0], -1, sizeof(dp[0])), dp[0][0] = 0;
    for (int i = 1; i <= n; i++)
    {
        memcpy(dp[i & 1], dp[(i & 1) ^ 1], sizeof(dp[(i & 1) ^ 1]));
        for (int j = 0; j < m; j++)
            if (dp[(i & 1) ^ 1][j] != -1)
            {
                int ptr = j;
                while (ptr != 0 && strA[i] != strB[ptr + 1])
                    ptr = nxt[ptr];
                if (strA[i] == strB[ptr + 1])
                    ptr++;
                dp[i & 1][ptr] = max(dp[i & 1][ptr], dp[(i & 1) ^ 1][j] + 1);
            }
    }
    int ans = 0;
    for (int i = 0; i < m; i++)
        ans = max(ans, dp[n & 1][i]);
    printf("%d", n - ans);
    return 0;
}