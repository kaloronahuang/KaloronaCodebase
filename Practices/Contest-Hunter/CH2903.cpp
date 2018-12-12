// CH2903.cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;
int stat[10][10], RQ, last[10][10][10], ans[20][3];
bool toRemove[10][10];
void copy(int step)
{
    for (int i = 1; i <= 5; i++)
        for (int j = 1; j <= 7; j++)
            last[step][i][j] = stat[i][j];
}
void copy_rev(int step)
{
    for (int i = 1; i <= 5; i++)
        for (int j = 1; j <= 7; j++)
            stat[i][j] = last[step][i][j];
}
void update()
{
    for (int i = 1; i <= 5; i++)
        for (int j = 1, x = 0; j <= 7; j++)
            if (!stat[i][j])
                x++;
            else if (x != 0)
                stat[i][j - x] = stat[i][j], stat[i][j] = 0;
}
bool check()
{
    for (int i = 1; i <= 5; i++)
        if (stat[i][1])
            return false;
    return true;
}
bool checkpt(int x, int y) { return (x > 0 && x <= 5 && y <= 7 && y > 0); }
bool remove()
{
    bool flag = true;
    for (int i = 1; i <= 5; i++)
        for (int j = 1; j <= 7; j++)
        {
            if (checkpt(i, j) && checkpt(i - 1, j) && checkpt(i + 1, j) &&
                stat[i][j] && stat[i][j] == stat[i - 1][j] && stat[i][j] == stat[i + 1][j])
                toRemove[i][j] = toRemove[i + 1][j] = toRemove[i - 1][j] = true, flag = false;
            if (checkpt(i, j) && checkpt(i, j - 1) && checkpt(i, j + 1) &&
                stat[i][j] && stat[i][j] == stat[i][j - 1] && stat[i][j] == stat[i][j + 1])
                toRemove[i][j] = toRemove[i][j + 1] = toRemove[i][j - 1] = true, flag = false;
        }
    if (flag)
        return false;
    for (int i = 1; i <= 5; i++)
        for (int j = 1; j <= 7; j++)
            if (toRemove[i][j])
                stat[i][j] = 0, toRemove[i][j] = false;
    return true;
}
void move(int i, int j, int x)
{
    swap(stat[i][j], stat[i + x][j]);
    update();
    while (remove())
        update();
}
void dfs(int remain)
{
    if (check())
    {
        for (int i = 1; i <= RQ; i++)
            printf("%d %d %d\n", ans[i][0], ans[i][1], ans[i][2]);
        exit(0);
    }
    if (remain == RQ + 1)
        return;
    copy(remain);
    for (int i = 1; i <= 5; i++)
        for (int j = 1; j <= 7; j++)
            if (stat[i][j])
            {
                if (checkpt(i + 1, j) && stat[i][j] != stat[i + 1][j])
                {
                    move(i, j, 1);
                    ans[remain][0] = i - 1, ans[remain][1] = j - 1, ans[remain][2] = 1;
                    dfs(remain + 1);
                    ans[remain][0] = -1, ans[remain][1] = -1, ans[remain][2] = -1;
                    copy_rev(remain);
                }
                if (checkpt(i - 1, j) && stat[i][j] != stat[i - 1][j])
                {
                    move(i, j, -1);
                    ans[remain][0] = i - 1, ans[remain][1] = j - 1, ans[remain][2] = -1;
                    dfs(remain + 1);
                    ans[remain][0] = -1, ans[remain][1] = -1, ans[remain][2] = -1;
                    copy_rev(remain);
                }
            }
}
int main()
{
    scanf("%d", &RQ);
    for (int i = 1; i <= 5; i++)
        for (int j = 1; j <= 8; j++)
        {
            scanf("%d", &stat[i][j]);
            if (stat[i][j] == 0)
                break;
        }
    memset(ans, -1, sizeof(ans));
    dfs(1);
    puts("-1");
    return 0;
}