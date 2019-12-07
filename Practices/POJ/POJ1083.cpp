// POJ1083.cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAX_N = 220;

int T, n, head[MAX_N], current, color[MAX_N];
bool used[MAX_N];

struct interval
{
    int l, r;
    bool operator<(const interval &rhs) const { return l < rhs.l || (l == rhs.l && r < rhs.r); }
} ints[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N * MAX_N];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        memset(head, -1, sizeof(head)), current = 0;
        memset(color, 0, sizeof(color)), memset(used, 0, sizeof(used));
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
        {
            scanf("%d%d", &ints[i].l, &ints[i].r);
            if (ints[i].l > ints[i].r)
                swap(ints[i].l, ints[i].r);
            if (!(ints[i].l & 1))
                ints[i].l--;
            if (ints[i].r & 1)
                ints[i].r++;
        }
        sort(ints + 1, ints + 1 + n);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (i != j)
                {
                    int l = max(ints[i].l, ints[j].l), r = min(ints[i].r, ints[j].r);
                    if (l <= r)
                        addpath(i, j);
                }
        for (int u = 1; u <= n; u++)
        {
            memset(used, 0, sizeof(used));
            for (int i = head[u]; i != -1; i = edges[i].nxt)
                if (edges[i].to < u)
                    used[color[edges[i].to]] |= true;
            for (int j = 1; j <= n; j++)
                if (used[j] == false)
                {
                    color[u] = j;
                    break;
                }
        }
        int mx = 0;
        for (int i = 1; i <= n; i++)
            mx = max(mx, color[i]);
        printf("%d\n", mx * 10);
    }
    return 0;
}