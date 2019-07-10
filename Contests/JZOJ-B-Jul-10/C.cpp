// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 51000;

int k, len, dp[MAX_N][30];
char str[MAX_N];

struct data
{
    int cnt[30], numOfTypes;
} database[MAX_N];

void print()
{
    puts("");
    for (int i = 1; i <= len / k; i++)
    {
        for (int ch = 1; ch <= 26; ch++)
            printf("%d ", dp[i][ch]);
        puts("");
    }
}

int main()
{
    scanf("%d%s", &k, str + 1), len = strlen(str + 1);
    for (int blk = 1; blk <= len / k; blk++)
        for (int cur = (blk - 1) * k + 1; cur <= blk * k; cur++)
            database[blk].numOfTypes += (database[blk].cnt[str[cur] - 'a' + 1] == 0) ? 1 : 0, database[blk].cnt[str[cur] - 'a' + 1]++;
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 1; i <= 26; i++)
        dp[1][i] = database[1].numOfTypes;
    for (int i = 2; i <= len / k; i++)
        for (int ch = 1; ch <= 26; ch++)
            if (database[i].cnt[ch])
                for (int prev_ch = 1; prev_ch <= 26; prev_ch++)
                    if (database[i - 1].cnt[prev_ch])
                        if (ch != prev_ch)
                            dp[i][ch] = min(dp[i][ch], dp[i - 1][prev_ch] + database[i].numOfTypes + ((database[i - 1].cnt[ch]) ? -1 : 0));
                        else
                            dp[i][ch] = min(dp[i][ch], dp[i - 1][prev_ch] + database[i].numOfTypes + ((database[i].numOfTypes == 1) ? -1 : 0));
    int ans = 0x3f3f3f3f;
    for (int i = 1; i <= 26; i++)
        if (database[len / k].cnt[i])
            ans = min(dp[len / k][i], ans);
    printf("%d", ans);
    return 0;
}