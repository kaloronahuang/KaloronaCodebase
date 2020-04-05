// triangles.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2020;

int n, tot, max_len, ptsx[int(1e5) + 200], ptsy[int(1e5) + 200], mat[4040][4040], pre[4040][4040];
char str[MAX_N];

void fileIO()
{
    freopen("triangles.in", "r", stdin);
    freopen("triangles.out", "w", stdout);
}

int main()
{
    fileIO();
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%s", str + 1);
        for (int j = 1; j <= n; j++)
            if (str[j] == '*')
                mat[i + j][i - j + n]++, ptsx[++tot] = i + j - 1, ptsy[tot] = i - j + n;
    }
    n <<= 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            pre[i][j] = pre[i][j - 1] + mat[i][j];
    int ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (mat[i][j])
                for (int k = j + 1; k <= n; k++)
                    if (mat[i][k])
                    {
                        int len = k - j + 1;
                        if (i - len + 1 >= 1)
                            ans += pre[i - len + 1][k] - pre[i - len + 1][j - 1];
                        if (i + len - 1 <= n)
                            ans += pre[i + len - 1][k] - pre[i + len - 1][j - 1];
                    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            pre[i][j] = pre[i - 1][j] + mat[i][j];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (mat[j][i])
                for (int k = j + 1; k <= n; k++)
                    if (mat[k][i])
                    {
                        int len = k - j + 1;
                        if (i - len + 1 >= 1)
                            ans += pre[k - 1][i - len + 1] - pre[j][i - len + 1];
                        if (i + len - 1 <= n)
                            ans += pre[k - 1][i + len - 1] - pre[j][i + len - 1];
                    }
    printf("%d\n", ans);
    return 0;
}