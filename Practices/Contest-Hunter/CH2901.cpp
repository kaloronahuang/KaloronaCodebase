// CH2901.cpp
#include <iostream>
#include <cstdio>
#define lowbit(num) (num & -num)
using namespace std;
const int VAL[9][9] = {{6, 6, 6, 6, 6, 6, 6, 6, 6},
                       {6, 7, 7, 7, 7, 7, 7, 7, 6},
                       {6, 7, 8, 8, 8, 8, 8, 7, 6},
                       {6, 7, 8, 9, 9, 9, 8, 7, 6},
                       {6, 7, 8, 9, 10, 9, 8, 7, 6},
                       {6, 7, 8, 9, 9, 9, 8, 7, 6},
                       {6, 7, 8, 8, 8, 8, 8, 7, 6},
                       {6, 7, 7, 7, 7, 7, 7, 7, 6},
                       {6, 6, 6, 6, 6, 6, 6, 6, 6}};

int map[81], X[81], Y[81], BOX[81], counter[(1 << 9)], slist[(1 << 9)];
int answer[81];
int sx[9], sy[9], sb[9], tmp, ans = 0;
void setStat(int pos, int k) { tmp = 1 << k, sx[X[pos]] ^= tmp, sy[Y[pos]] ^= tmp, sb[BOX[pos]] ^= tmp; }
int getCnt(int num)
{
    int cnt = 0;
    while (num > 0)
        cnt++, num -= lowbit(num);
    return cnt;
}
int getFactor(int pos)
{
    if (X[pos] == 0 || X[pos] == 8 || Y[pos] == 0 || Y[pos] == 8)
        return 6;
    if (X[pos] == 1 || X[pos] == 7 || Y[pos] == 1 || Y[pos] == 7)
        return 7;
    if (X[pos] == 2 || X[pos] == 6 || Y[pos] == 2 || Y[pos] == 6)
        return 8;
    if (X[pos] == 3 || X[pos] == 5 || Y[pos] == 3 || Y[pos] == 5)
        return 9;
    return 10;
}
void dfs(int remain, int prev)
{
    if (!remain)
    {
        if (ans < prev)
        {
            ans = prev;
            for (int i = 0; i < 81; i++)
                answer[i] = map[i];
        }
        return;
    }
    int min_val = 2e9, id;
    for (int i = 0; i < 81; i++)
        if (map[i] == 0)
        {
            int stat = sx[X[i]] & sy[Y[i]] & sb[BOX[i]];
            if (stat == 0)
                return;
            if (counter[stat] < min_val)
                min_val = counter[stat], id = i;
        }
    int stat = sx[X[id]] & sy[Y[id]] & sb[BOX[id]];
    while (stat > 0)
    {
        int digit = slist[lowbit(stat)];
        setStat(id, digit);
        map[id] = digit + 1;
        dfs(remain - 1, prev + VAL[X[id]][Y[id]] * (digit + 1));
        setStat(id, digit);
        map[id] = 0;
        stat -= lowbit(stat);
    }
}
int main()
{
    for (int i = 0; i < 81; i++)
        scanf("%d", &map[i]);
    for (int i = 0; i < 81; i++)
        X[i] = i / 9, Y[i] = i % 9, BOX[i] = (int)(X[i] / 3) * 3 + (int)(Y[i] / 3);
    for (int i = 0; i < 9; i++)
        slist[1 << i] = i;
    for (int i = 0; i < (1 << 9); i++)
        counter[i] = getCnt(i);
    for (int i = 0; i < 81; i++)
        sx[i] = sy[i] = sb[i] = (1 << 9) - 1;
    int rm = 81;
    for (int i = 0; i < 81; i++)
        if (map[i] != 0)
            setStat(i, map[i] - 1), rm--;
    dfs(rm, 0);
    int sum = 0;
    for (int i = 0; i < 81; i++)
        sum += (answer[i]) * VAL[X[i]][Y[i]];
    if (ans == 0)
        printf("-1");
    else
        printf("%d", sum);
    return 0;
}