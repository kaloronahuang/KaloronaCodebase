// P2924.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 300;

struct edge
{
    int idA, idB;
    double x, y;
    bool operator<(const edge &e) const { return atan2(x, y) < atan2(e.x, e.y); }
} nodes[MAX_N * MAX_N], pt[MAX_N];

int n, current, dp[MAX_N], ans;

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lf%lf", &pt[i].x, &pt[i].y);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (i != j)
            {
                nodes[++current].idA = i, nodes[current].idB = j;
                nodes[current].x = pt[j].x - pt[i].x;
                nodes[current].y = pt[j].y - pt[i].y;
            }
    sort(nodes + 1, nodes + 1 + current);
    for (int i = 1; i <= n; i++)
    {
        memset(dp, -62, sizeof(dp));
        dp[i] = 0;
        for (int j = 1; j <= current; j++)
            dp[nodes[j].idB] = max(dp[nodes[j].idB], dp[nodes[j].idA] + 1);
        ans = max(ans, dp[i]);
    }
    printf("%d", ans);
    return 0;
}