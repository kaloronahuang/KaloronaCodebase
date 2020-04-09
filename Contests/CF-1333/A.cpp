// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 110;

int T, n, m;
char str[MAX_N][MAX_N];

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                str[i][j] = 'B';
        str[1][1] = 'W';
        for (int i = 1; i <= n; i++, puts(""))
            for (int j = 1; j <= m; j++)
                printf("%c", str[i][j]);
    }
    return 0;
}