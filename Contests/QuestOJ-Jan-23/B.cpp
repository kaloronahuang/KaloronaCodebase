// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 110;

int matrix[MAX_N][MAX_N], n;

int id(int x, int y) { return (x - 1) * n + y - 1; }

int main()
{
    scanf("%d", &n);
    int gans = 0;
    for (int stat = 0; stat < (1 << (n * n)); stat++)
    {
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                matrix[i][j] = ((stat >> id(i, j)) & 1);
        int gcnt = 0;
        for (int i = 1; i <= n; i++)
        {
            int pcnt = 0;
            for (int j = 1; j <= n; j++)
                pcnt += matrix[i][j];
            gcnt += (pcnt == 0 || pcnt == n);
        }
        for (int i = 1; i <= n; i++)
        {
            int pcnt = 0;
            for (int j = 1; j <= n; j++)
                pcnt += matrix[j][i];
            gcnt += (pcnt == 0 || pcnt == n);
        }
        if (gcnt & 1)
            gans++;
    }
    printf("%d\n", gans);
    return 0;
}