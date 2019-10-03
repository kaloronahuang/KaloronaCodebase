// Yukari.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, xl, yl, xr, yr, tot;

struct interval
{
    int l, r;
    bool whole;
    interval intersect(interval target)
    {
        return whole ? target : interval{max(target.l, l), min(target.r, r)};
    }
    bool valid() { return whole || l <= r; }
};

struct node
{
    int x, val;
    bool operator<(const node &nd) const { return x < nd.x; }
} nodes[MAX_N << 2];

int main()
{
    freopen("camera.in", "r", stdin);
    freopen("camera.out", "w", stdout);
    scanf("%d%d%d%d%d", &n, &xl, &yl, &xr, &yr);
    for (int i = 1; i <= n; i++)
    {
        int xi, yi, ui, vi;
        scanf("%d%d%d%d", &xi, &yi, &ui, &vi);
        interval x_int, y_int;
        if (ui == 0)
        {
            x_int.whole = (xl <= xi && xi <= xr);
            if (!x_int.whole)
                continue;
        }
        else if (ui > 0)
            x_int = {(int)ceil(double(xl - xi) / double(ui)), (int)floor(double(xr - xi) / double(ui))};
        else
            x_int = {(int)ceil(double(xr - xi) / double(ui)), (int)floor(double(xl - xi) / double(ui))};
        if (vi == 0)
        {
            y_int.whole = (yl <= yi && yi <= yr);
            if (!y_int.whole)
                continue;
        }
        else if (vi > 0)
            y_int = {(int)ceil(double(yl - yi) / double(vi)), (int)floor(double(yr - yi) / double(vi))};
        else
            y_int = {(int)ceil(double(yr - yi) / double(vi)), (int)floor(double(yl - yi) / double(vi))};
        /*
        interval x_int = {(int)ceil(double(xl - xi) / double(ui)), (int)floor(double(xr - xi) / double(ui))};
        if (ui < 0)
            swap(x_int.l, x_int.r);
        x_int.l = max(x_int.l, 1);
        interval y_int = {(int)ceil(double(yl - yi) / double(vi)), (int)floor(double(yr - yi) / double(vi))};
        if (vi < 0)
            swap(y_int.l, y_int.r);
        y_int.l = max(y_int.l, 1);
        */
        if (x_int.valid() && y_int.valid())
        {
            interval ist = x_int.intersect(y_int);
            if (ist.whole)
                nodes[++tot] = node{1, 1};
            else if (ist.valid())
                nodes[++tot] = node{ist.l, 1}, nodes[++tot] = node{ist.r + 1, -1};
        }
    }
    sort(nodes + 1, nodes + 1 + tot);
    int ans = 0, val = 0;
    for (int i = 1, prefix = 0; i <= tot; i++)
    {
        prefix += nodes[i].val;
        if (prefix > val)
            ans = nodes[i].x, val = prefix;
    }
    printf("%d", max(ans, 0));
    return 0;
}