// CF1280B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 110;

int T, n, m;
char mp[MAX_N][MAX_N];
map<int, int> ext;

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++)
            scanf("%s", mp[i] + 1);
        int ans = 1e9;
        bool sideFlag = false, cornerFlag = false, tmp = true, Aflag = false, AatSide = false;
        int siz = 0;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                if (mp[i][j] == 'A')
                {
                    Aflag = true;
                    AatSide |= ((i == 1 || i == n) || (j == 1 || j == m));
                    siz++;
                }
        if (siz == n * m)
            ans = 0;
        if (Aflag)
            ans = min(ans, 4);
        if (AatSide)
            ans = min(ans, 3);
        for (int i = 1; i <= n; i++)
            tmp &= mp[i][1] == 'A';
        sideFlag |= tmp, tmp = true;
        for (int i = 1; i <= n; i++)
            tmp &= mp[i][m] == 'A';
        sideFlag |= tmp, tmp = true;
        for (int i = 1; i <= m; i++)
            tmp &= mp[1][i] == 'A';
        sideFlag |= tmp, tmp = true;
        for (int i = 1; i <= m; i++)
            tmp &= mp[n][i] == 'A';
        sideFlag |= tmp, tmp = true;
        cornerFlag = ((mp[1][1] == 'A') || (mp[1][m] == 'A') || (mp[n][1] == 'A') || (mp[n][m] == 'A'));
        if (sideFlag)
            ans = min(ans, 1);
        if (cornerFlag)
            ans = min(ans, 2);
        ext[0] = true;
        for (int j = 1; j <= m; j++)
            for (int i = 1; i <= n + 1; i++)
                if (mp[i][j] != 'A')
                {
                    ext[i - 1] = 1;
                    if (j == 1 || j == m)
                        ext[i - 1] = 2;
                    break;
                }
        for (int j = 1; j <= m; j++)
            for (int i = n; i >= 0; i--)
                if (mp[i][j] != 'A' && ext[i])
                {
                    if (ext[i] == 2)
                        ans = min(ans, 2);
                    else
                        ans = min(ans, 3);
                    break;
                }
                else if (mp[i][j] != 'A')
                    break;
        ext.clear();
        ext[0] = true;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m + 1; j++)
                if (mp[i][j] != 'A')
                {
                    ext[j - 1] = 1;
                    if (i == 1 || i == n)
                        ext[j - 1] = 2;
                    break;
                }
        for (int i = 1; i <= n; i++)
            for (int j = m; j >= 0; j--)
                if (mp[i][j] != 'A' && ext[j])
                {
                    if (ext[j] == 2)
                        ans = min(ans, 2);
                    else
                        ans = min(ans, 3);
                    break;
                }
                else if (mp[i][j] != 'A')
                    break;
        ext.clear();
        if (ans == 1e9)
            printf("MORTAL\n");
        else
            printf("%d\n", ans);
    }
    return 0;
}