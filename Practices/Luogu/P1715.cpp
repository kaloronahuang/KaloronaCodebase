// P1715.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 330;

int n, down[MAX_N][MAX_N], ans[MAX_N];

struct node
{
    int x, y;
    bool operator<(const node &rhs) const { return x < rhs.x || (x == rhs.x && y < rhs.y); }
} nodes[MAX_N];

bool check(int l, int r, int mid)
{
    if (nodes[l].x <= nodes[mid].x && nodes[mid].x <= nodes[r].x)
    {
        double k = double(nodes[r].y - nodes[l].y) / double(nodes[r].x - nodes[l].x);
        double b = nodes[l].y - k * nodes[l].x;
        return nodes[mid].y < k * nodes[mid].x + b;
    }
    return false;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &nodes[i].x, &nodes[i].y);
    sort(nodes + 1, nodes + 1 + n);
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            for (int k = i + 1; k < j; k++)
                down[i][j] += check(i, j, k) == true;
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            for (int k = j + 1; k <= n; k++)
                ans[abs(down[i][j] + down[j][k] - down[i][k] + check(i, k, j))]++;
    for (int i = 0; i <= n - 3; i++)
        printf("%d\n", ans[i]);
    return 0;
}