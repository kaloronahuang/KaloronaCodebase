// CF1163D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1010;

int dp[MAX_N][55][55], L, LA, LB, nxt_a[MAX_N], nxt_b[MAX_N], go_a[MAX_N][26], go_b[MAX_N][26];
char str[MAX_N], sA[MAX_N], sB[MAX_N];

void get_nxt(int nxt[], int len, char s[], int go[][26])
{
    nxt[1] = 0;
    for (int i = 2, j; i <= len; i++)
    {
        j = nxt[i - 1];
        while (j > 0 && s[j + 1] != s[i])
            j = nxt[j];
        if (s[j + 1] == s[i])
            j++;
        nxt[i] = j;
    }
    for (int i = 0; i <= len; i++)
        for (int c = 0; c < 26; c++)
        {
            int j = i;
            while (j > 0 && s[j + 1] != (c + 'a'))
                j = nxt[j];
            if (s[j + 1] == (c + 'a'))
                j++;
            go[i][c] = j;
        }
}

int main()
{
    scanf("%s%s%s", str + 1, sA + 1, sB + 1);
    L = strlen(str + 1), LA = strlen(sA + 1), LB = strlen(sB + 1);
    get_nxt(nxt_a, LA, sA, go_a), get_nxt(nxt_b, LB, sB, go_b);
    for (int i = 0; i <= L; i++)
        for (int x = 0; x <= LA; x++)
            for (int y = 0; y <= LB; y++)
                dp[i][x][y] = -0x3f3f3f3f;
    dp[0][0][0] = 0;
    for (int i = 0; i < L; i++)
        for (int x = 0; x <= LA; x++)
            for (int y = 0; y <= LB; y++)
                for (int c = 0; c < 26; c++)
                    if (str[i + 1] == c + 'a' || str[i + 1] == '*')
                    {
                        int nA = go_a[x][c], nB = go_b[y][c];
                        dp[i + 1][nA][nB] = max(dp[i + 1][nA][nB], dp[i][x][y] + (nA == LA) - (nB == LB));
                    }
    int ans = -0x3f3f3f3f;
    for (int x = 0; x <= LA; x++)
        for (int y = 0; y <= LB; y++)
            ans = max(ans, dp[L][x][y]);
    printf("%d", ans);
    return 0;
}