// P3439.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

typedef unsigned long long ll;

int n;

struct node
{
    int x, y, w;
} nodes[MAX_N], xbas[MAX_N], ybas[MAX_N];

ll count(int x, int y)
{
    ll ret = 0;
    for (int i = 1; i <= n; i++)
        ret += ll(1) * nodes[i].w * ll(1) * max(abs(nodes[i].x - x), abs(nodes[i].y - y));
    return ret;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1, x, y; i <= n; i++)
        scanf("%d%d%d", &x, &y, &nodes[i].w), nodes[i].x = x, nodes[i].y = y, xbas[i] = ybas[i] = node{x + y, x - y, nodes[i].w};
    sort(xbas + 1, xbas + 1 + n, [](const node &rhs1, const node &rhs2) { return rhs1.x < rhs2.x; });
    sort(ybas + 1, ybas + 1 + n, [](const node &rhs1, const node &rhs2) { return rhs1.y < rhs2.y; });
    int l = 1, r = n;
    while (l < r)
        if (xbas[l].w < xbas[r].w)
            xbas[r].w -= xbas[l].w, l++;
        else if (xbas[l].w > xbas[r].w)
            xbas[l].w -= xbas[r].w, r--;
        else
            l++, r--;
    int ptx = xbas[l].x;
    l = 1, r = n;
    while (l < r)
        if (ybas[l].w < ybas[r].w)
            ybas[r].w -= ybas[l].w, l++;
        else if (ybas[l].w > ybas[r].w)
            ybas[l].w -= ybas[r].w, r--;
        else
            l++, r--;
    int pty = ybas[l].y;
    int x = (ptx + pty) / 2, y = (ptx - pty) / 2, key = 0;
    int dx[4] = {0, 1, 0, 1}, dy[4] = {0, 0, 1, 1};
    ll ret = 0xffffffffffffffff;
    for (int i = 0; i < 4; i++)
    {
        ll res = count(x + dx[i], y + dy[i]);
        if (res < ret)
            key = i, ret = res;
    }
    printf("%d %d\n", x + dx[key], y + dy[key]);
    return 0;
}