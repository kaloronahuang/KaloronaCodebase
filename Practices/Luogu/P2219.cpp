// P2219.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 1010;
int outer[MAX_N][MAX_N], center[MAX_N][MAX_N], whole[MAX_N][MAX_N];
int p[MAX_N][MAX_N], q[MAX_N][MAX_N], que[MAX_N * MAX_N];
int n, m, a, b, c, d;
int main()
{
    scanf("%d%d%d%d%d%d", &n, &m, &a, &b, &c, &d);
    // preprocessing;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &whole[i][j]);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            whole[i][j] += whole[i - 1][j] + whole[i][j - 1] - whole[i - 1][j - 1];
    for (int i = a; i <= n; i++)
        for (int j = b; j <= m; j++)
            outer[i][j] = whole[i][j] - whole[i - a][j] - whole[i][j - b] + whole[i - a][j - b];
    for (int i = c; i <= n; i++)
        for (int j = d; j <= m; j++)
            center[i][j] = whole[i][j] - whole[i - c][j] - whole[i][j - d] + whole[i - c][j - d];
    // start to work!
    for (int i = 1; i <= n; i++)
    {
        int l = 1, r = 0;
        for (int j = 1; j <= m; j++)
        {
            while (l <= r && j - que[l] + 1 >= b - d)
                l++;
            while (l <= r && center[i][j] <= center[i][que[r]])
                r--;
            que[++r] = j;
            p[i][j] = center[i][que[l]];
        }
    }
    for (int i = 1; i <= m; i++)
    {
        int l = 1, r = 0;
        for (int j = 1; j <= n; j++)
        {
            while (l <= r && j - que[l] + 1 >= a - c)
                l++;
            while (l <= r && p[j][i] <= p[que[r]][i])
                r--;
            que[++r] = j;
            q[j][i] = p[que[l]][i];
        }
    }
    long long ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            ans = max(ans, (long long)(outer[i][j] - q[i - 1][j - 1]));
    printf("%lld", ans);
    return 0;
}