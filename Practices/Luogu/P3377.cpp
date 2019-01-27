// P3377.cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int MAX_N = 100020;
struct node
{
    int lson, rson, val, dist, fa;
} nodes[MAX_N];
int tmp;
int merge(int x, int y)
{
    if (!x || !y)
        return x + y;
    if (nodes[x].val > nodes[y].val || (nodes[x].val == nodes[y].val) && x > y)
        swap(x, y);
    int &ul = nodes[x].lson, &ur = nodes[x].rson;
    ur = merge(ur, y);
    nodes[ur].fa = x;
    if (nodes[ul].dist < nodes[ur].dist)
        swap(ul, ur);
    nodes[x].dist = nodes[ur].dist + 1;
    return x;
}
int getf(int x)
{
    while (nodes[x].fa)
        x = nodes[x].fa;
    return x;
}
void pop(int x)
{
    nodes[x].val = -1;
    nodes[nodes[x].lson].fa = nodes[nodes[x].rson].fa = 0;
    merge(nodes[x].lson, nodes[x].rson);
}
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    nodes[0].dist = -1;
    for (int i = 1; i <= n; i++)
        scanf("%d", &tmp), nodes[i].val = tmp;
    for (int i = 1; i <= m; i++)
    {
        int com;
        scanf("%d", &com);
        if (com == 1)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            if (x == y || nodes[x].val == -1 || nodes[y].val == -1)
                continue;
            merge(getf(x), getf(y));
        }
        else
        {
            int x;
            scanf("%d", &x);
            if (nodes[x].val == -1)
                printf("-1\n");
            else
            {
                int y = getf(x);
                printf("%d\n", nodes[y].val);
                pop(y);
            }
        }
    }
    return 0;
}