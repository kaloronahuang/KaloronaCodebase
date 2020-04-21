// BZ1941.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 501000, INF = 0x3f3f3f3f;

int n, current_frame, groot, ans_max, ans_min;

struct point
{
    int d[2];
    bool operator<(const point &rhs) const { return d[current_frame] < rhs.d[current_frame] || (d[current_frame] == rhs.d[current_frame] && d[current_frame ^ 1] < rhs.d[current_frame ^ 1]); }
} pts[MAX_N];

struct node
{
    int ch[2], d[2], mx[2], mn[2];
    int &operator[](const int &idx) { return ch[idx]; }
} nodes[MAX_N];

void pushup(int p)
{
    for (int i = 0; i < 2; i++)
    {
        nodes[p].mx[i] = nodes[p].mn[i] = nodes[p].d[i];
        for (int j = 0; j < 2; j++)
            if (nodes[p][j])
                nodes[p].mx[i] = max(nodes[p].mx[i], nodes[nodes[p][j]].mx[i]), nodes[p].mn[i] = min(nodes[p].mn[i], nodes[nodes[p][j]].mn[i]);
    }
}

int build(int l, int r)
{
    if (l > r)
        return 0;
    int mid = (l + r) >> 1;
    nth_element(pts + l, pts + mid, pts + r + 1);
    for (int i = 0; i < 2; i++)
        nodes[mid].d[i] = nodes[mid].mx[i] = nodes[mid].mn[i] = pts[mid].d[i];
    current_frame ^= 1;
    nodes[mid][0] = build(l, mid - 1), nodes[mid][1] = build(mid + 1, r);
    current_frame ^= 1;
    pushup(mid);
    return mid;
}

int getRectMax(int x, int y, int p) { return max(x - nodes[p].mn[0], nodes[p].mx[0] - x) + max(y - nodes[p].mn[1], nodes[p].mx[1] - y); }

int getRectMin(int x, int y, int p) { return max(x - nodes[p].mx[0], 0) + max(nodes[p].mn[0] - x, 0) + max(y - nodes[p].mx[1], 0) + max(nodes[p].mn[1] - y, 0); }

void queryMax(int p, int x, int y)
{
    if (p == 0)
        return;
    if (!(nodes[p].d[0] == x && nodes[p].d[1] == y))
        ans_max = max(ans_max, abs(x - nodes[p].d[0]) + abs(y - nodes[p].d[1]));
    int dist[2] = {-INF, -INF};
    if (nodes[p][0])
        dist[0] = getRectMax(x, y, nodes[p][0]);
    if (nodes[p][1])
        dist[1] = getRectMax(x, y, nodes[p][1]);
    int t = (dist[0] <= dist[1]);
    if (dist[t] > ans_max)
        queryMax(nodes[p][t], x, y);
    t ^= 1;
    if (dist[t] > ans_max)
        queryMax(nodes[p][t], x, y);
}

void queryMin(int p, int x, int y)
{
    if (p == 0)
        return;
    if (!(nodes[p].d[0] == x && nodes[p].d[1] == y))
        ans_min = min(ans_min, abs(x - nodes[p].d[0]) + abs(y - nodes[p].d[1]));
    int dist[2] = {INF, INF};
    if (nodes[p][0])
        dist[0] = getRectMin(x, y, nodes[p][0]);
    if (nodes[p][1])
        dist[1] = getRectMin(x, y, nodes[p][1]);
    int t = (dist[0] >= dist[1]);
    if (dist[t] < ans_min)
        queryMin(nodes[p][t], x, y);
    t ^= 1;
    if (dist[t] < ans_min)
        queryMin(nodes[p][t], x, y);
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &pts[i].d[0], &pts[i].d[1]);
    groot = build(1, n);
    int ans = INF;
    for (int i = 1; i <= n; i++)
    {
        ans_min = INF, ans_max = -INF;
        queryMax(groot, pts[i].d[0], pts[i].d[1]);
        queryMin(groot, pts[i].d[0], pts[i].d[1]);
        ans = min(ans, ans_max - ans_min);
    }
    printf("%d\n", ans);
    return 0;
}