// P2216.cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <deque>
#define pr pair<int, int>
using namespace std;
const int MX_A = 1020, MX_N = 200;
int a, b, n, mat[MX_A][MX_A], maxrow[MX_A][MX_A], minrow[MX_A][MX_A], Ymx[MX_A][MX_A], Ymi[MX_A][MX_A];
int main()
{
    scanf("%d%d%d", &a, &b, &n);
    for (int i = 1; i <= a; i++)
        for (int j = 1; j <= b; j++)
            scanf("%d", &mat[i][j]);
    deque<int> dqx, dqi;
    for (int i = 1; i <= a; i++)
    {
        dqx.clear(), dqi.clear();
        dqx.push_front(1), dqi.push_back(1);
        for (int j = 2; j <= b; j++)
        {
            while (!dqx.empty() && mat[i][j] >= mat[i][dqx.back()])
                dqx.pop_back();
            while (!dqi.empty() && mat[i][j] <= mat[i][dqi.back()])
                dqi.pop_back();
            dqx.push_back(j), dqi.push_back(j);
            while (!dqx.empty() && j - dqx.front() >= n)
                dqx.pop_front();
            while (!dqi.empty() && j - dqi.front() >= n)
                dqi.pop_front();
            if (j >= n)
                maxrow[i][j - n + 1] = mat[i][dqx.front()], minrow[i][j - n + 1] = mat[i][dqi.front()];
        }
    }
    for (int i = 1; i <= b - n + 1; i++)
    {
        dqx.clear(), dqi.clear();
        dqx.push_front(1), dqi.push_back(1);
        for (int j = 2; j <= a; j++)
        {
            while (!dqx.empty() && maxrow[j][i] >= maxrow[dqx.back()][i])
                dqx.pop_back();
            while (!dqi.empty() && minrow[j][i] <= minrow[dqi.back()][i])
                dqi.pop_back();
            dqx.push_back(j), dqi.push_back(j);
            while (!dqx.empty() && j - dqx.front() >= n)
                dqx.pop_front();
            while (!dqi.empty() && j - dqi.front() >= n)
                dqi.pop_front();
            if (j >= n)
                Ymx[j - n + 1][i] = maxrow[dqx.front()][i], Ymi[j - n + 1][i] = minrow[dqi.front()][i];
        }
    }
    int ans = 2e9;
    for (int i = 1; i <= a - n + 1; i++)
        for (int j = 1; j <= b - n + 1; j++)
            ans = min(ans, Ymx[i][j] - Ymi[i][j]);
    printf("%d", ans);
    return 0;
}