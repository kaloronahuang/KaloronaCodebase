// LOJ6030.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1010;

int n;
char str[MAX_N][MAX_N], curt[MAX_N][MAX_N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%s", str[i] + 1);
    bool flag = true;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (str[i][j] == '#')
                flag = false;
    if (flag)
        puts("-1"), exit(0);
    int cnt = n;
    for (int i = 1; i <= n; i++)
    {
        bool flag = true;
        for (int j = 1; j <= n; j++)
            if (str[j][i] == '.')
                flag = false;
        cnt -= (flag == true);
    }
    if (cnt == 0)
        puts("0"), exit(0);
    int ans = 0x3f3f3f3f;
    for (int i = 1; i <= n; i++)
    {
        int blank = 0;
        bool exist = false;
        for (int j = 1; j <= n; j++)
            blank += (str[i][j] == '.');
        for (int j = 1; j <= n; j++)
            if (str[j][i] == '#')
                exist = true;
        if (exist)
            ans = min(ans, cnt + blank);
        else
            ans = min(ans, cnt + blank + 1);
    }
    printf("%d\n", ans);
    return 0;
}