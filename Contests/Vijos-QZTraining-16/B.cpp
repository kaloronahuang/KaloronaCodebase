// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 100010;

char str[MAX_N], tmp[20];
bool g[30][30];
int n, pre[MAX_N][30], opt[MAX_N], ans, T;

int main()
{
    scanf("%d%s", &n, str);
    for (int i = 0; i < 26; i++)
        pre[0][i] = -1;
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < 26; j++)
            pre[i][j] = pre[i - 1][j];
        pre[i][str[i - 1] - 'a'] = i - 1;
    }
    scanf("%d", &T);
    while (T--)
    {
        scanf("%s", tmp);
        g[tmp[0] - 'a'][tmp[1] - 'a'] = g[tmp[1] - 'a'][tmp[0] - 'a'] = 1;
    }
    ans = opt[0] = 1;
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < 26; j++)
            if (!g[j][str[i] - 'a'] && pre[i][j] != -1)
                opt[i] = max(opt[i], opt[pre[i][j]] + 1);
            else
                opt[i] = max(opt[i], 1);
        ans = max(ans, opt[i]);
    }
    printf("%d", n - ans);
    return 0;
}