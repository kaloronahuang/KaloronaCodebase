// CH0201.cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
const int maxn = 600;
int map[10][10], org[10][10];
void change(int x, int y)
{
    map[x][y] ^= 1;
    map[x - 1][y] ^= 1, map[x][y - 1] ^= 1;
    map[x + 1][y] ^= 1, map[x][y + 1] ^= 1;
}
int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        int ans = 0x3f3f3f3f;
        int tmp = 0;
        for (int i = 1; i <= 5; i++)
        {
            string ln;
            cin >> ln;
            for (int c = 1; c <= 5; c++)
                org[i][c] = ln[c - 1] - '0';
        }
        for (int i = 0; i < 32; i++)
        {
            tmp = 0;
            for (int x = 1; x <= 5; x++)
                for (int y = 1; y <= 5; y++)
                    map[x][y] = org[x][y];

            for (int j = 1; j <= 5; j++)
                if (i & (1 << (j - 1)))
                    change(1, j), tmp++;

            for (int j = 1; j <= 4; j++)
                for (int k = 1; k <= 5; k++)
                    if (map[j][k] == 0)
                        change(j + 1, k), tmp++;

            bool flag = true;
            for (int x = 1; x <= 5; x++)
                for (int y = 1; y <= 5; y++)
                    if (map[x][y] == 0 && flag)
                    {
                        flag = false;
                        break;
                    }
            if (flag)
                ans = min(ans, tmp);
        }
        ans = (ans > 6) ? -1 : ans;
        printf("%d\n", ans);
    }
    return 0;
}