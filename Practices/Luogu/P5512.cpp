// P5512.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 11;

int matrix[MAX_N][MAX_N], n, prime[MAX_N * MAX_N * 2], tot;
bool jud[MAX_N * MAX_N][MAX_N * MAX_N], vis[MAX_N * MAX_N * 2], tag[MAX_N];

void dfs(int ln, int col)
{
    if (col == n + 1)
    {
        dfs(ln + 1, 1);
        return;
    }
    if (ln == n + 1)
    {
        for (int i = 1; i <= n; i++, puts(""))
            for (int j = 1; j <= n; j++)
                printf("%d ", matrix[i][j]);
        exit(0);
    }
    if (ln == 1 || col == 1)
    {
        for (int i = 1; i <= n * n; i++)
            if (!tag[i] && jud[i][matrix[ln - 1][col]] && jud[i][matrix[ln][col - 1]])
            {
                matrix[ln][col] = i, tag[i] = true;
                dfs(ln, col + 1);
                tag[i] = false, matrix[ln][col] = 0;
            }
    }
    else
    {
        for (int i = n * n; i >= 1; i--)
            if (!tag[i] && jud[i][matrix[ln - 1][col]] && jud[i][matrix[ln][col - 1]])
            {
                matrix[ln][col] = i, tag[i] = true;
                dfs(ln, col + 1);
                tag[i] = false, matrix[ln][col] = 0;
            }
    }
}

int main()
{
    for (int i = 2; i < MAX_N * MAX_N * 2; i++)
    {
        if (!vis[i])
            prime[++tot] = i;
        for (int j = 1; j <= tot && i * prime[j] < MAX_N * MAX_N * 2; j++)
        {
            vis[i * prime[j]] = true;
            if (i % prime[j] == 0)
                break;
        }
    }
    scanf("%d", &n);
    if (n == 1)
        puts("NO"), exit(0);
    for (int i = 1; i <= n * n; i++)
        jud[0][i] = jud[i][0] = true;
    for (int i = 1; i <= n * n; i++)
        for (int j = 1; j <= n * n; j++)
            if (!vis[i + j])
                jud[i][j] = jud[j][i] = true;
    matrix[1][1] = 1, tag[1] = true;
    dfs(1, 2);
    puts("NO");
    return 0;
}