// POJ3076.cpp
#include <iostream>
#include <cstdio>
using namespace std;
char map[256];
int counter[(1 << 16)], slist[(1 << 16)], X[256], Y[256], BOX[256];
int sx[16], sy[16], sb[16], tmp;
void set(int idx, int pos) { tmp = 1 << pos, sx[X[idx]] ^= tmp, sy[Y[idx]] ^= tmp, sb[BOX[idx]] ^= tmp; }
inline int lowbit(int x) { return x & (-x); }
inline int count(int num)
{
    int cnt = 0;
    while (num > 0)
        cnt++, num -= lowbit(num);
    return cnt;
}
bool dfs(int remain)
{
    if (remain == 0)
        return true;
    int min_val = 20, val_id;
    for (int pos = 0; pos < 256; pos++)
        if (map[pos] == '-')
        {
            int comb = sx[X[pos]] & sy[Y[pos]] & sb[BOX[pos]];
            if (counter[comb] < min_val)
                val_id = pos, min_val = counter[comb];
        }
    int k = sx[X[val_id]] & sy[Y[val_id]] & sb[BOX[val_id]];
    while (k > 0)
    {
        int digit = slist[lowbit(k)];
        map[val_id] = 'A' + digit;
        set(val_id, digit);
        if (dfs(remain - 1))
            return true;
        set(val_id, digit);
        map[val_id] = '-';
        k -= lowbit(k);
    }
    return false;
}
int main()
{
    int lst = 0;
    for (int i = 1; i <= 16; i++)
        scanf("%s", map + lst), lst += 16;
    for (int i = 0; i < (1 << 16); i++)
        counter[i] = count(i);
    for (int i = 0; i < 16; i++)
        slist[1 << i] = i;
    for (int i = 0; i < 256; i++)
        sx[i] = sy[i] = sb[i] = (1 << 16) - 1;
    for (int i = 0; i < 256; i++)
        X[i] = i % 16, Y[i] = i / 16, BOX[i] = X[i] / 4 + (int)(Y[i] / 4) * 4;
    int tot = 0;
    for (int i = 0; i < 256; i++)
        if (map[i] != '-')
            set(i, map[i] - 'A');
        else
            tot++;
    if (dfs(tot))
        for (int i = 0; i < 16; i++)
        {
            for (int j = 0; j < 16; j++)
                printf("%c", map[i * 16 + j]);
            printf("\n");
        }
    return 0;
}