// left.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 21;

int n, pi[10], table[10][10], tmp[MAX_N], pre[MAX_N];

int getId(int x, int y) { return x * (1 << (n - 1)) + y; }

void solve(int level, int posx, int posy)
{
}

void output()
{
    for (int i = 1; i <= (2 * n - 1); i++, puts(""))
        for (int j = 1; j <= (1 << (n - 1)); j++)
            printf("%d", table[i][j]);
}

void conduct(int inp1, int inp2, int out1, int out2, int x, int y)
{
    tmp[out1] = pre[inp1], tmp[out2] = pre[inp2];
    if (table[x][y])
        swap(tmp[out1], tmp[out2]);
}

int main()
{
    while (scanf("%d", &n) && n)
    {
        for (int i = 0; i < (1 << n); i++)
            scanf("%d", &pi[i]);
        int mat_siz = (2 * n - 1) * (1 << (n - 1));
        bool found = false;
        for (int stat = 0; stat < (1 << mat_siz); stat++)
        {
            for (int i = 0; i < (1 << n); i++)
                pre[i] = i;
            for (int i = 0; i < 2 * n - 1; i++)
                for (int j = 0; j < 1 << (n - 1); j++)
                    table[2 * n - 1 - i][(1 << (n - 1)) - j] = (stat >> getId(i, j)) & 1;

            // solve(3);
            if (n == 1)
            {
                conduct(0, 1, 0, 1, 1, 1);
                memcpy(pre, tmp, sizeof(pre));
            }
            if (n == 2)
            {
                conduct(0, 1, 0, 2, 1, 1);
                conduct(2, 3, 1, 3, 1, 2);
                memcpy(pre, tmp, sizeof(pre));
                conduct(0, 1, 0, 2, 2, 1);
                conduct(2, 3, 1, 3, 2, 2);
                memcpy(pre, tmp, sizeof(pre));
                conduct(0, 1, 0, 1, 3, 1);
                conduct(2, 3, 2, 3, 3, 2);
                memcpy(pre, tmp, sizeof(pre));
            }
            if (n == 3)
            {
                conduct(0, 1, 0, 4, 1, 1);
                conduct(2, 3, 1, 5, 1, 2);
                conduct(4, 5, 2, 6, 1, 3);
                conduct(6, 7, 3, 7, 1, 4);
                memcpy(pre, tmp, sizeof(pre));
                conduct(0, 1, 0, 2, 2, 1);
                conduct(2, 3, 1, 3, 2, 2);
                conduct(4, 5, 4, 6, 2, 3);
                conduct(6, 7, 5, 7, 2, 4);
                memcpy(pre, tmp, sizeof(pre));
                conduct(0, 1, 0, 2, 3, 1);
                conduct(2, 3, 1, 3, 3, 2);
                conduct(4, 5, 4, 6, 3, 3);
                conduct(6, 7, 5, 7, 3, 4);
                memcpy(pre, tmp, sizeof(pre));
                conduct(0, 1, 0, 2, 4, 1);
                conduct(2, 3, 4, 6, 4, 2);
                conduct(4, 5, 1, 3, 4, 3);
                conduct(6, 7, 5, 7, 4, 4);
                memcpy(pre, tmp, sizeof(pre));
                conduct(0, 1, 0, 1, 5, 1);
                conduct(2, 3, 2, 3, 5, 2);
                conduct(4, 5, 4, 5, 5, 3);
                conduct(6, 7, 6, 7, 5, 4);
                memcpy(pre, tmp, sizeof(pre));
            }

            bool flag = true;
            for (int i = 0; i < (1 << n); i++)
                flag &= (tmp[i] == pi[i]);
            if (flag)
            {
                output(), found = true;
                break;
            }
        }
        if (!found)
            puts("-1");
    }
    return 0;
}