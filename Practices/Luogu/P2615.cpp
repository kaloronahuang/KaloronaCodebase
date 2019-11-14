// P2615.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 40;

int mat[MAX_N][MAX_N], n;
pair<int, int> pos[MAX_N * MAX_N];

int main()
{
    scanf("%d", &n);
    mat[1][(n >> 1) + 1] = 1, pos[1] = make_pair(1, (n >> 1) + 1);
    for (int i = 2; i <= n * n; i++)
    {
        if (pos[i - 1].first == 1 && pos[i - 1].second != n)
            mat[n][pos[i - 1].second + 1] = i, pos[i] = make_pair(n, pos[i - 1].second + 1);
        else if (pos[i - 1].second == n && pos[i - 1].first != 1)
            mat[pos[i - 1].first - 1][1] = i, pos[i] = make_pair(pos[i - 1].first - 1, 1);
        else if (pos[i - 1].first == 1 && pos[i - 1].second == n)
            mat[pos[i - 1].first + 1][pos[i - 1].second] = i, pos[i] = make_pair(pos[i - 1].first + 1, pos[i - 1].second);
        else
        {
            if (mat[pos[i - 1].first - 1][pos[i - 1].second + 1] == 0)
                mat[pos[i - 1].first - 1][pos[i - 1].second + 1] = i, pos[i] = make_pair(pos[i - 1].first - 1, pos[i - 1].second + 1);
            else
                mat[pos[i - 1].first + 1][pos[i - 1].second] = i, pos[i] = make_pair(pos[i - 1].first + 1, pos[i - 1].second);
        }
    }
    for (int i = 1; i <= n; i++, puts(""))
        for (int j = 1; j <= n; j++)
            printf("%d ", mat[i][j]);
    return 0;
}