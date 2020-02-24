// CF1261C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e6 + 200;

int n, m;

struct accessPointChar
{
    char str[MAX_N];

    void scan()
    {
        for (int i = 1; i <= n; i++)
            scanf("%s", str + 1 + i * (m + 1));
    }

    void clear(char content = 0) { memset(str, content, sizeof(str)); }

    char *operator[](const int idx) { return str + idx * (m + 1); }

    void output()
    {
        for (int i = 1; i <= n; i++, puts(""))
            for (int j = 1; j <= m; j++)
                printf("%c", (*this)[i][j]);
    }
} mp, tree_set;

struct accessPointInt
{
    int str[MAX_N];

    void clear() { memset(str, 0, sizeof(str)); }

    int *operator[](const int idx) { return str + idx * (m + 1); }
} prefixSum, dot;

int tree_set_num;

bool check(int threshold)
{
    tree_set_num = 0;
    tree_set.clear('.'), dot.clear();
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (mp[i][j] == 'X')
            {
                int lftX = i - threshold, lftY = j - threshold;
                int rigX = i + threshold, rigY = j + threshold;
                bool lft = (lftX <= n && lftX >= 1) && (lftY <= m && lftY >= 1);
                bool rig = (rigX <= n && rigX >= 1) && (rigY <= m && rigY >= 1);
                if (lft && rig && prefixSum[rigX][rigY] - prefixSum[lftX - 1][rigY] - prefixSum[rigX][lftY - 1] + prefixSum[lftX - 1][lftY - 1] == (rigX - lftX + 1) * (rigY - lftY + 1))
                {
                    tree_set_num++, tree_set[i][j] = 'X';
                    if (rigX < n && rigY < m)
                        dot[rigX + 1][rigY + 1]++;
                    if (rigY < m)
                        dot[lftX][rigY + 1]--;
                    if (rigX < n)
                        dot[rigX + 1][lftY]--;
                    dot[lftX][lftY]++;
                }
            }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            dot[i][j] += dot[i - 1][j] + dot[i][j - 1] - dot[i - 1][j - 1];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            dot[i][j] = dot[i - 1][j] + dot[i][j - 1] - dot[i - 1][j - 1] + (dot[i][j] > 0);
    return (dot[n][m] <= prefixSum[n][m] && tree_set_num > 0);
}

int main()
{
    scanf("%d%d", &n, &m);
    mp.scan(), prefixSum.clear();
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            prefixSum[i][j] = prefixSum[i - 1][j] + prefixSum[i][j - 1] - prefixSum[i - 1][j - 1] + (mp[i][j] == 'X');
    int l = 0, r = max(n, m), res;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (check(mid))
            l = mid + 1, res = mid;
        else
            r = mid - 1;
    }
    check(res);
    if (dot[n][m] != prefixSum[n][m])
        puts("0"), mp.output(), exit(0);
    printf("%d\n", res);
    tree_set.output();
    return 0;
}