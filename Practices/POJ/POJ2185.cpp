// POJ2185.cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#define reg register
using namespace std;
const int maxn = 11000;
int R, C, seg[maxn], nxt[maxn];
char src[maxn][80], tmp[maxn];
int main()
{
    scanf("%d%d", &R, &C);
    for (int i = 1; i <= R; i++)
    {
        scanf("%s", src[i] + 1);
        strcpy(tmp + 1, src[i] + 1);
        for (int len = C; len > 1; len--)
        {
            tmp[len] = 0;
            int x, y;
            for (x = 1, y = 1; y <= C; x++, y++)
            {
                if (!tmp[x])
                    x = 1;
                if (src[i][y] != tmp[x])
                    break;
            }
            if (y == C + 1)
                seg[len]++;
        }
    }
    int width = C + 1;
    for (int i = 1; i <= C; i++)
        if (seg[i] == R)
        {
            width = i;
            break;
        }
    for (int i = 1; i <= R; i++)
        src[i][width] = 0;
    nxt[1] = 0;
    for (int i = 2, k = 0; i <= R; i++)
    {
        while (k && strcmp(src[i] + 1, src[k + 1] + 1))
            k = nxt[k];
        if (!strcmp(src[i] + 1, src[k + 1] + 1))
            k++;
        nxt[i] = k;
    }
    printf("%d\n", (width - 1) * (R - nxt[R]));
    return 0;
}