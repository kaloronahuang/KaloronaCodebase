// A.cpp
#include <bits/stdc++.h>
#define pr pair<int, int>

using namespace std;

const int MAX_N = 1010, dix[4] = {0, 0, 1, -1}, diy[4] = {-1, 1, 0, 0};

int mat[MAX_N][MAX_N], n, m, water[MAX_N][MAX_N];
bool vis[MAX_N][MAX_N];

struct tup
{
    int x, y, height;
    bool operator<(const tup &nd) const { return height > nd.height; }
};

int main()
{
    priority_queue<tup> pq;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            scanf("%d", &mat[i][j]), water[i][j] = mat[i][j];
            if (i == 1 || i == n || j == 1 || j == m)
                vis[i][j] = true, pq.push(tup{i, j, mat[i][j]});
        }
    while (!pq.empty())
    {
        tup curt = pq.top();
        pq.pop();
        for (int i = 0; i < 4; i++)
        {
            int dx = dix[i] + curt.x, dy = diy[i] + curt.y;
            if (dx >= 1 && dx <= n && dy >= 1 && dy <= m && vis[dx][dy] == false)
            {
                vis[dx][dy] = true;
                water[dx][dy] = max(water[dx][dy], curt.height);
                pq.push(tup{dx, dy, water[dx][dy]});
            }
        }
    }
    long long ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            ans += water[i][j] - mat[i][j];
    printf("%lld", ans);
    return 0;
}