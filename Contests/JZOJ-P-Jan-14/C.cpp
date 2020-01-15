// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1100, mod = 1e9 + 7;

int n, m, dp[MAX_N][MAX_N], si[MAX_N], tmp[MAX_N], curt[MAX_N], answer[MAX_N];
char str[MAX_N];

int main()
{
    scanf("%s%d", str + 1, &m), n = strlen(str + 1);
    for (int i = 1; i <= n; i++)
        if (str[i] == 'A')
            si[i] = 1;
        else if (str[i] == 'G')
            si[i] = 2;
        else if (str[i] == 'T')
            si[i] = 3;
        else
            si[i] = 4;
    dp[0][0] = 1;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < (1 << n); j++)
            if (dp[i][j])
                for (int c = 1; c <= 4; c++)
                {
                    memset(tmp, 0, sizeof(tmp));
                    for (int ptr = 1; ptr <= n; ptr++)
                        if (j & (1 << (ptr - 1)))
                            tmp[n - ptr + 1] = 1;
                    for (int ptr = 1; ptr <= n; ptr++)
                        tmp[ptr] += tmp[ptr - 1];
                    int new_stat = 0;
                    for (int ptr = 1; ptr <= n; ptr++)
                    {
                        curt[ptr] = max(curt[ptr - 1], tmp[ptr]);
                        if (c == si[ptr])
                            curt[ptr] = max(tmp[ptr - 1] + 1, curt[ptr]);
                        new_stat = (new_stat << 1) | (curt[ptr] - curt[ptr - 1]);
                    }
                    dp[i + 1][new_stat] = (0LL + dp[i + 1][new_stat] + dp[i][j]) % mod;
                }
    for (int i = 0; i < (1 << n); i++)
        answer[__builtin_popcount(i)] = (0LL + answer[__builtin_popcount(i)] + dp[m][i]) % mod;
    for (int i = 0; i <= n; i++)
        printf("%d\n", answer[i]);
    return 0;
}