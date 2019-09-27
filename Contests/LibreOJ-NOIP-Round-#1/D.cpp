// D.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 550, UP_BOUND = 2e6 + 200;

int n, cnt;
bool matrix[MAX_N][MAX_N];

ll getSiz(ll nodeNum) { return nodeNum * (nodeNum - 1) * (nodeNum - 2) / 6; }

int main()
{
    scanf("%d", &n);
    // component size;
    for (int i = 500; i >= 3; i--)
    {
        if (getSiz(i) <= n)
        {
            n -= getSiz(i);
            // make a component;
            for (int x = cnt + 1; x <= cnt + i; x++)
                for (int y = cnt + 1; y <= cnt + i; y++)
                    matrix[x][y] = matrix[y][x] = true;
            cnt += i, i++;
        }
    }
    printf("%d\n", cnt);
    for (int i = 1; i <= cnt; i++, puts(""))
        for (int j = i + 1; j <= cnt; j++)
            printf("%d ", (matrix[i][j] == true) ? 1 : 0);
    return 0;
}