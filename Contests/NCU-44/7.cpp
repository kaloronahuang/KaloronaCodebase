// 7.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 110;
const int dx[] = {-1, 1, 0, 0}, dy[] = {0, 0, -1, 1};

int n, aff[MAX_N * MAX_N];
char mp[MAX_N][MAX_N];

int getId(int x, int y) { return (x - 1) * n + y; }

int find(int x) { return (aff[x] == x ? x : aff[x] = find(aff[x])); }

int main()
{
    scanf("%d", &n);
    int ext = n * n + 1;
    aff[ext] = ext;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            aff[getId(i, j)] = getId(i, j);
    for (int i = 1; i <= n; i++)
        for (int j = 1, tmp; j <= n; j++)
            scanf("%d", &tmp), mp[i][j] = tmp + '0';
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (mp[i][j] == '0')
                for (int d = 0; d < 4; d++)
                {
                    int tx = i + dx[d], ty = j + dy[d];
                    if (mp[i][j] == mp[tx][ty] && find(getId(i, j)) != find(getId(tx, ty)))
                        aff[find(getId(i, j))] = find(getId(tx, ty));
                    if (mp[i][j] == '0' && (tx == 0 || tx == n + 1 || ty == 0 || ty == n + 1) && find(getId(i, j)) != find(ext))
                        aff[find(getId(i, j))] = find(ext);
                }
    for (int i = 1; i <= n; i++, puts(""))
        for (int j = 1; j <= n; j++)
            if (find(getId(i, j)) == find(ext) || mp[i][j] == '1')
                printf("%c ", mp[i][j]);
            else
                printf("2 ");
    return 0;
}