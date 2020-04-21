// LOJ2586.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 6e5 + 200, INF = 0x7f7f7f7f;
const double cosa = sqrt(2) / 2, sina = cosa, eps = 5e-2;

int n, current_frame, ans[MAX_N], groot;

inline char nc()
{
    static char buf[10000000], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 10000000, stdin), p1 == p2) ? EOF : *p1++;
}

int read()
{
    int x = 0, f = 1;
    char ch = nc();
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = nc();
    }
    while (isdigit(ch))
        x = (x << 3) + (x << 1) + ch - '0', ch = nc();
    return x * f;
}

struct point
{
    double x, y, r;
    int id;
    bool operator<(const point &rhs) const
    {
        if (current_frame == 0)
            return x < rhs.x;
        if (current_frame == 1)
            return y < rhs.y;
        return r == rhs.r ? id < rhs.id : r > rhs.r;
    }
} pts[MAX_N], org[MAX_N];

struct node
{
    int ch[2];
    double mx[2], mn[2];

    int &operator[](const int &rhs) { return ch[rhs]; }
} nodes[MAX_N];

double pow2(double x) { return x * x; }

void pushup(int p)
{
    nodes[p].mx[0] = pts[p].x + pts[p].r, nodes[p].mx[1] = pts[p].y + pts[p].r;
    nodes[p].mn[0] = pts[p].x - pts[p].r, nodes[p].mn[1] = pts[p].y - pts[p].r;
    for (int i = 0; i < 2; i++)
        if (nodes[p][i])
            for (int j = 0; j < 2; j++)
                nodes[p].mx[j] = max(nodes[p].mx[j], nodes[nodes[p][i]].mx[j]), nodes[p].mn[j] = min(nodes[p].mn[j], nodes[nodes[p][i]].mn[j]);
}

int build(int l, int r)
{
    if (l > r)
        return 0;
    int mid = (l + r) >> 1;
    nth_element(pts + l, pts + mid, pts + r + 1);
    current_frame ^= 1;
    nodes[mid][0] = build(l, mid - 1), nodes[mid][1] = build(mid + 1, r);
    current_frame ^= 1, pushup(mid);
    return mid;
}

void modify(int p, point curt)
{
    if (p == 0 || curt.x - curt.r > nodes[p].mx[0] || curt.x + curt.r < nodes[p].mn[0] || curt.y - curt.r > nodes[p].mx[1] || curt.y + curt.r < nodes[p].mn[1])
        return;
    if (ans[pts[p].id] == 0)
        if (pow2(pts[p].x - curt.x) + pow2(pts[p].y - curt.y) <= pow2(pts[p].r + curt.r) + eps)
            ans[pts[p].id] = curt.id, pts[p].x = pts[p].y = 0, pts[p].r = -INF;
    modify(nodes[p][0], curt), modify(nodes[p][1], curt), pushup(p);
}

int main()
{
    freopen("32", "r", stdin);
    freopen("test.out", "w", stdout);
    n = read();
    for (int i = 1, x, y, r; i <= n; i++)
    {
        x = read(), y = read(), r = read();
        pts[i].x = 1.0 * x * cosa - 1.0 * y * sina;
        pts[i].y = 1.0 * x * sina + 1.0 * y * cosa;
        pts[i].id = i, pts[i].r = r;
    }
    current_frame = 2, sort(pts + 1, pts + 1 + n), current_frame = 0;
    memcpy(org, pts, sizeof(org)), groot = build(1, n);
    for (int i = 1; i <= n; i++)
        if (ans[org[i].id] == 0)
            modify(groot, org[i]);
    for (int i = 1; i <= n; i++)
        printf("%d ", ans[i]);
    return 0;
}