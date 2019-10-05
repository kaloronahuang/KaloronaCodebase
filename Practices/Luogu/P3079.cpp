// P3079.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 50505;

int n, ans;

struct node
{
    int x1, y1, x2, y2;
    bool operator<(const node &nd) const { return x1 < nd.x1; }
} nodes[MAX_N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d%d%d", &nodes[i].x1, &nodes[i].y1, &nodes[i].x2, &nodes[i].y2);
    sort(nodes + 1, nodes + 1 + n), ans = n;
    for (int lft = 1, rig = 2; rig <= n; rig++)
    {
        while (nodes[lft].x2 <= nodes[rig].x1)
            lft++;
        for (int i = lft; i < rig; i++)
            if (nodes[i].y1 < nodes[rig].y1 && nodes[rig].x2 < nodes[i].x2 && nodes[i].y2 > nodes[rig].y2)
            {
                ans--;
                break;
            }
    }
    printf("%d", ans);
    return 0;
}