// P1058.cpp
#include <bits/stdc++.h>

using namespace std;

int height[55][55], n, m, mxy, mix = 0x3f3f3f3f;
char mat[1010][330];

void drawRawRectangle(int x, int y)
{
    mix = min(mix, x - 3), mxy = max(mxy, y + 4);
    mat[x][y] = mat[x][y + 4] = '+';
    mat[x - 3][y] = mat[x - 3][y + 4] = '+';
    for (int i = y + 1; i <= y + 3; i++)
        mat[x][i] = mat[x - 3][i] = '-';
    for (int i = x - 1; i >= x - 2; i--)
        mat[i][y] = mat[i][y + 4] = '|';
    for (int i = x - 1; i >= x - 2; i--)
        for (int j = y + 1; j <= y + 3; j++)
            mat[i][j] = ' ';
}

void drawCube(int x, int y)
{
    drawRawRectangle(x - 2, y + 2);
    drawRawRectangle(x, y);
    mat[x - 4][y + 1] = mat[x - 4][y + 5] = mat[x - 1][y + 5] = '/';
    mat[x - 4][y + 2] = mat[x - 2][y + 5] = ' ';
}

void print()
{
    for (int i = mix; i <= 1000; i++, puts(""))
        for (int j = 1; j <= mxy; j++)
            putchar(mat[i][j]);
}

int main()
{
    memset(mat, '.', sizeof(mat));
    scanf("%d%d", &n, &m);
    for (int i = n; i >= 1; i--)
        for (int j = 1; j <= m; j++)
        {
            scanf("%d", &height[i][j]);
            for (int z = 1; z <= height[i][j]; z++)
            {
                int x = 1000 - (i - 1) * 2 - (z - 1) * 3, y = 1 + (i - 1) * 2 + (j - 1) * 4;
                drawCube(x, y);
            }
        }
    print();
    return 0;
}