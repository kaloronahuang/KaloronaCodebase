// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 105;

int T, n;
short mask[MAX_N][MAX_N];
char players[MAX_N], res[MAX_N][MAX_N];

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        memset(res, 0, sizeof(res));
        scanf("%d%s", &n, players + 1);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                mask[i][j] = 7;
        for (int cplayer = 1; cplayer <= n; cplayer++)
            if (players[cplayer] == '1')
            {
                for (int i = cplayer - 1; i >= 1; i--)
                    mask[i][cplayer] &= 6;
                for (int i = cplayer + 1; i <= n; i++)
                    mask[cplayer][i] &= 3;
            }
        bool flag = true;
        for (int cplayer = 1; cplayer <= n && flag; cplayer++)
            if (players[cplayer] == '2')
            {
                bool rflag = false;
                for (int i = cplayer - 1; i >= 1; i--)
                    if (mask[i][cplayer] & 4)
                    {
                        mask[i][cplayer] = 4, rflag = true;
                        break;
                    }
                for (int i = cplayer + 1; i <= n; i++)
                    if (mask[cplayer][i] & 1)
                    {
                        mask[cplayer][i] = 1, rflag = true;
                        break;
                    }
                flag &= rflag;
            }
        if (!flag)
            puts("NO");
        else
        {
            puts("YES");
            for (int i = 1; i <= n; i++)
                for (int j = i; j <= n; j++)
                    if (i == j)
                        res[i][j] = 'X';
                    else if (mask[i][j] & 2)
                        res[i][j] = res[j][i] = '=';
                    else if (mask[i][j] & 1)
                        res[i][j] = '+', res[j][i] = '-';
                    else if (mask[i][j] & 4)
                        res[i][j] = '-', res[j][i] = '+';
            for (int i = 1; i <= n; i++)
                printf("%s\n", res[i] + 1);
        }
    }
    return 0;
}