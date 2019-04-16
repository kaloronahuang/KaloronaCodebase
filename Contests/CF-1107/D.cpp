// D.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 5300;
int n, mat[MAX_N][MAX_N], prefix[MAX_N][MAX_N], upb = 0x3f3f3f3f;
int getNum(char ch)
{
    if (ch <= '9' && ch >= '0')
        return ch - '0';
    return 10 + ch - 'A';
}
bool check(int blk)
{
    int tot = n / blk;
    for (int i = 1; i <= tot; i++)
        for (int j = 1; j <= tot; j++)
        {
            int x = blk * i, y = blk * j;
            int ans = prefix[x][y] - prefix[x - blk][y] - prefix[x][y - blk] + prefix[x - blk][y - blk];
            if (ans == blk * blk || ans == 0)
                continue;
            else
                return false;
        }
    return true;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n / 4; j++)
        {
            char ch = getchar();
            while (ch == '\n')
                ch = getchar();
            int num = getNum(ch);
            for (int k = 0; k < 4; k++)
                mat[i][(j - 1) * 4 + k + 1] = (num >> (3 - k)) & 1;
        }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            prefix[i][j] = prefix[i - 1][j] + prefix[i][j - 1] - prefix[i - 1][j - 1] + mat[i][j];
    // horizontial
    for (int i = 1; i <= n; i++)
    {
        int lst = 1;
        for (int j = 1; j <= n; j++)
            if (mat[i][j] != mat[i][lst])
                upb = min(upb, j - lst + 1), lst = j;
    }
    for (int i = 1; i <= n; i++)
    {
        int lst = 1;
        for (int j = 1; j <= n; j++)
            if (mat[j][i] != mat[lst][i])
                upb = min(upb, j - lst + 1), lst = j;
    }
    int ans = 1;
    for (int i = 2; i <= n; i++)
        if (n % i == 0 && check(i))
            ans = max(ans, i);
    printf("%d", ans);
    return 0;
}