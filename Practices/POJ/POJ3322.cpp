// POJ3322.cpp
#include <iostream>
#include <cstdio>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;
const int maxb = 510;
// 0 left, 1 right, 2 up, 3 down;
const int next_x[3][4] = {{0, 0, -2, 1}, {0, 0, -1, 1}, {0, 0, -1, 2}};
const int next_y[3][4] = {{-2, 1, 0, 0}, {-1, 2, 0, 0}, {-1, 1, 0, 0}};
const int dx[4] = {0, 0, -1, 1}, dy[4] = {-1, 1, 0, 0};
const int dir[3][4] = {{1, 1, 2, 2}, {0, 0, 1, 1}, {2, 2, 0, 0}};
int N, M, cnt[maxb][maxb][4];
char map[maxb][maxb];
struct vec
{
    int x, y, lieleft;
    bool operator==(const vec &tar) const { return x == tar.x && y == tar.y && lieleft == tar.lieleft; }
} st, ed;
queue<vec> qpool;
bool validiate(int x, int y) { return (x > 0 && x <= N) && (y > 0 && y <= M); }
bool validiate(vec v)
{
    if (v.lieleft == 1)
        return validiate(v.x, v.y) && validiate(v.x, v.y + 1) && map[v.x][v.y] != '#' && map[v.x][v.y + 1] != '#';
    else if (v.lieleft == 2)
        return validiate(v.x, v.y) && validiate(v.x + 1, v.y) && map[v.x][v.y] != '#' && map[v.x + 1][v.y] != '#';
    else if (v.lieleft == 0)
        return validiate(v.x, v.y) && map[v.x][v.y] == '.';
}
void handle_sp()
{
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= M; j++)
            if (map[i][j] == 'X')
                for (int k = 0; k < 3; k++)
                {
                    int x = i + dx[k], y = j + dy[k];
                    if (validiate(x, y) && map[x][y] == 'X')
                    {
                        st.x = min(i, x), st.y = min(j, y);
                        st.lieleft = (k < 2) ? 1 : 2;
                        map[i][j] = map[x][y] = '.';
                        break;
                    }
                    if (map[i][j] == 'X')
                        st.x = i, st.y = j, st.lieleft = 0;
                }
            else if (map[i][j] == 'O')
                map[i][j] = '.', ed.x = i, ed.y = j, ed.lieleft = 0;
}
int bfs()
{
    // emptify the queue;
    while (!qpool.empty())
        qpool.pop();
    memset(cnt, -1, sizeof(cnt));
    qpool.push(st);
    cnt[st.x][st.y][st.lieleft] = 0;
    // start to bfs;
    while (!qpool.empty())
    {
        vec curt = qpool.front();
        qpool.pop();
        for (int i = 0; i < 4; i++)
        {
            vec vst = curt;
            vst.x += next_x[vst.lieleft][i], vst.y += next_y[vst.lieleft][i];
            vst.lieleft = dir[vst.lieleft][i];
            if (validiate(vst) && cnt[vst.x][vst.y][vst.lieleft] == -1)
            {
                cnt[vst.x][vst.y][vst.lieleft] = cnt[curt.x][curt.y][curt.lieleft] + 1;
                qpool.push(vst);
                if (vst == ed)
                    return cnt[vst.x][vst.y][vst.lieleft];
            }
        }
    }
    return -1;
}
int main()
{
    while (scanf("%d%d", &N, &M) && N != 0)
    {
        for (int i = 1; i <= N; i++)
            scanf("%s", map[i] + 1);
        handle_sp();
        int ans = bfs();
        if (ans == -1)
            puts("Impossible");
        else
            printf("%d\n", ans);
    }
    return 0;
}