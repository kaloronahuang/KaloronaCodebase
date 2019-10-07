// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3, mod = 7;

int n, matrix[MAX_N][MAX_N], tmp[MAX_N][MAX_N];
string str;

void mul()
{
    memset(matrix, 0, sizeof(matrix));
    for (int i = 1; i <= 2; i++)
        for (int j = 1; j <= 2; j++)
            for (int k = 1; k <= 2; k++)
                (matrix[i][j] += tmp[i][k] * tmp[k][j] % mod) %= mod;
}

int main()
{
    while (cin >> str)
    {
        memset(matrix, 0, sizeof(matrix));
        memset(tmp, 0, sizeof(tmp));
        for (int i = 1; i <= 2; i++)
            for (int j = 1; j <= 2; j++)
                scanf("%d", &matrix[i][j]);
        if (str.length() > 4)
        {
            printf("%d %d\n%d %d\n", 1, 0, 0, 1);
            return 0;
        }

        n = str[0] - '0';
        for (int i = 1; i <= n - 1; i++)
            memcpy(tmp, matrix, sizeof(tmp)), mul();
        for (int i = 1; i <= 2; i++)
        {
            for (int j = 1; j <= 2; j++)
                printf("%d ", matrix[i][j]);
            puts("");
        }
    }
    return 0;
}