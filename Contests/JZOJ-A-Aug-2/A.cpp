// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 60100;

struct point
{
    int x, y, prop, id;
    bool operator<(const point &pt) const { return prop < pt.prop; }
} nodes[MAX_N], *cur[MAX_N];

int n, m;
char opt[10];

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d%d%d", &nodes[i].x, &nodes[i].y, &nodes[i].prop), nodes[i].id = i;
    sort(nodes + 1, nodes + 1 + n);
    for (int i = 1; i <= n; i++)
        cur[nodes[i].id] = &nodes[i];
    while (m--)
    {
        scanf("%s", opt + 1);
        int x, y, x_, y_, k;
        if (opt[1] == 'Q')
        {
            scanf("%d%d%d%d%d", &x, &y, &x_, &y_, &k);
            bool flag = false;
            for (int i = 1; i <= n; i++)
                if (nodes[i].x <= max(x, x_) && nodes[i].x >= min(x, x_) && nodes[i].y <= max(y, y_) && nodes[i].y >= min(y, y_))
                {
                    k--;
                    if (k == 0)
                    {
                        printf("%d\n", nodes[i].prop), flag = true;
                        break;
                    }
                }
            if (!flag)
                puts("It doesn't exist.");
        }
        else
        {
            scanf("%d%d", &x, &y), x++, y++;
            swap(cur[x]->x, cur[y]->x), swap(cur[x]->y, cur[y]->y);
            swap(cur[x]->id, cur[y]->id), swap(cur[x], cur[y]);
        }
    }
    return 0;
}