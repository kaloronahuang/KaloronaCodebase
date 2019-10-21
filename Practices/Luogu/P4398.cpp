// P4398.cpp
#include <bits/stdc++.h>
#define ull unsigned long long

using namespace std;

const int MAX_N = 55, bitnum = 399;

int n, matA[MAX_N][MAX_N], matB[MAX_N][MAX_N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            scanf("%d", &matA[i][j]);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            scanf("%d", &matB[i][j]);
    for (int len = n; len >= 1; len--)
        for (int i = 1; i + len - 1 <= n; i++)
            for (int j = 1; j + len - 1 <= n; j++)
                for (int x = 1; x + len - 1 <= n; x++)
                    for (int y = 1; y + len - 1 <= n; y++)
                    {
                        bool flag = true;
                        for (int posx = 1; posx <= len; posx++)
                        {
                            for (int posy = 1; posy <= len; posy++)
                                if (matA[i + posx - 1][j + posy - 1] != matB[x + posx - 1][y + posy - 1])
                                {
                                    flag = false;
                                    break;
                                }
                            if (!flag)
                                break;
                        }
                        if (flag)
                            printf("%d\n", len), exit(0);
                    }
    return 0;
}