// POJ3074.cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#define lowbit(number) (number & (-number))
using namespace std;
char sequence[81];
int X[81], Y[81], Box[81], slist[(1 << 9)], counters[(1 << 9)];
int sx[81], sy[81], sb[81], n, tmp;
void setStat(int i, int k) { tmp = 1 << k, sx[X[i]] ^= tmp, sy[Y[i]] ^= tmp, sb[Box[i]] ^= tmp; }
int getSlot(int num)
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
    int min_val = 10, val_id;
    for (int i = 0; i < 81; i++)
        if (sequence[i] == '.')
        {
            int comb = sx[X[i]] & sy[Y[i]] & sb[Box[i]];
            if (counters[comb] < min_val)
                min_val = counters[comb], val_id = i;
        }
    int comb = sx[X[val_id]] & sy[Y[val_id]] & sb[Box[val_id]];
    while (comb > 0)
    {
        int nbit = slist[lowbit(comb)];
        sequence[val_id] = nbit + '1';
        setStat(val_id, nbit);
        if (dfs(remain - 1))
            return true;
        setStat(val_id, nbit);
        sequence[val_id] = '.';
        comb -= lowbit(comb);
    }
    return false;
}
int main()
{
    for (int i = 0; i < 81; i++)
        X[i] = i / 9, Y[i] = i % 9, Box[i] = (int)(X[i] / 3) * 3 + Y[i] / 3;
    for (int i = 0; i < 9; i++)
        slist[1 << i] = i;
    for (int i = 0; i < (1 << 9); i++)
        counters[i] = getSlot(i);
    while (scanf("%s", sequence) && sequence[0] != 'e')
    {
        // initailize the fact;
        n = 0;
        for (int i = 0; i < 81; i++)
            sx[i] = sy[i] = sb[i] = (1 << 9) - 1;
        for (int i = 0; i < 81; i++)
            if (sequence[i] != '.')
                setStat(i, sequence[i] - '1');
            else
                n++;
        if (dfs(n))
            printf("%s\n", sequence);
    }
    return 0;
}