// A.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll mat[2020][2020], n, m, ans, strd, height[2020][2020];
int order[2020 * 2020];
int getPos(int x, int y) { return (x - 1) * m + y; }
pair<int, int> getPos(int num) { return make_pair((num - 1) / m + 1, (num - 1) % m + 1); }
bool cmp(int a, int b) { return mat[getPos(a).first][getPos(a).second] < mat[getPos(b).first][getPos(b).second]; }
int main()
{
    scanf("%lld%lld", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%lld", &mat[i][j]), strd = max(strd, mat[i][j]), order[getPos(i, j)] = getPos(i, j);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            height[i][j] = strd;
    sort(order + 1, order + 1 + getPos(n, m));
    for (int tim = 1; tim <= 100; tim++)
        for (int i = 1; i <= getPos(n, m); i++)
        {
            int x = getPos(order[i]).first, y = getPos(order[i]).second;
            height[x][y] = max(mat[x][y], min(height[x][y], min(height[x - 1][y], min(height[x + 1][y], min(height[x][y + 1], height[x][y - 1])))));
        }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            ans += height[i][j] - mat[i][j];
    printf("%lld", ans);
    return 0;
}