// POJ3322.cpp
#include <iostream>
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
const int maxb = 510;
// 0 left, 1 right, 2 up, 3 down;
const int next_x[3][4] = {{{0,0,-2,1}}}
int N, M, cnt[maxb][maxb][4];
char map[maxb][maxb];
struct vec
{
    int x, y, lieleft;
};
queue<vec> qpool;
bool validiate(int x, int y) { return (x > 0 && x <= N) && (y > 0 && y <= M); }
bool validiate(vec v)
{
    if (v.lieleft == 1)
        return validiate(v.x, v.y) && validiate(v.x, v.y + 1) && map[v.x][v.y] != '#' && map[v.x][v.y + 1] != '#';
    else if (v.lieleft == 2)
        return validiate(v.x, v.y) && validiate(v.x - 1, v.y) && map[v.x][v.y] != '#' && map[v.x - 1][v.y] != '#';
    else if (v.lieleft == 0)
        return validiate(v.x, v.y) && map[v.x][v.y] == '.';
}
int main()
{
    while (scanf("%d%d", &N, &M) && N != 0)
    {
        for (int i = 1; i <= N; i++)
            scanf("%s", map[i] + 1);
    }
    return 0;
}