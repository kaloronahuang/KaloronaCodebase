// UOJ553.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 12200;

int n, q, current_frame, groot;

struct node
{
    int d[2], sum, max_val[2], min_val[2], ch[2];
    bool operator<(const node &rhs) const { return d[current_frame] < rhs.d[current_frame] || (d[current_frame] == rhs.d[current_frame] && d[current_frame ^ 1] < rhs.d[current_frame ^ 1]); }
} nodes[MAX_N];

char nc()
{
    static char buff[1 << 20], *p1 = buff, *p2 = buff;
    return p1 == p2 && (p2 = (p1 = buff) + fread(buff, 1, 1 << 20, stdin), p1 == p2) ? EOF : *p1++;
}

int read()
{
    register int x = 0, f = 1;
    char c = nc();
    while (!isdigit(c))
    {
        if (c == '-')
            f = -1;
        c = nc();
    }
    while (isdigit(c))
        x = (x << 3) + (x << 1) + c - '0', c = nc();
    return (f == 1) ? x : -x;
}

void pushup(int p)
{
    memcpy(nodes[p].max_val, nodes[p].d, sizeof(nodes[p].d));
    memcpy(nodes[p].min_val, nodes[p].d, sizeof(nodes[p].d));
    nodes[p].sum = 1;
    for (int c = 0; c < 2; c++)
        if (nodes[p].ch[c])
        {
            nodes[p].sum += nodes[nodes[p].ch[c]].sum;
            for (int i = 0; i < 2; i++)
            {
                nodes[p].max_val[i] = max(nodes[p].max_val[i], nodes[nodes[p].ch[c]].max_val[i]);
                nodes[p].min_val[i] = min(nodes[p].min_val[i], nodes[nodes[p].ch[c]].min_val[i]);
            }
        }
}

int calc(int l, int r)
{
    double ax = 0, ay = 0, bx = 0, by = 0, len = r - l + 1;
    for (int i = l; i <= r; i++)
    {
        ax += nodes[i].d[0], bx += nodes[i].d[1];
        ay += 1.0 * nodes[i].d[0] * nodes[i].d[0];
        by += 1.0 * nodes[i].d[1] * nodes[i].d[1];
    }
    ax = ay * len - ax * ax, bx = by * len - bx * bx;
    return ax <= bx;
}

int build(int l, int r)
{
    if (l > r)
        return 0;
    int mid = (l + r) >> 1;
    current_frame = calc(l, r);
    nth_element(nodes + l, nodes + mid, nodes + r + 1);
    nodes[mid].ch[0] = build(l, mid - 1), nodes[mid].ch[1] = build(mid + 1, r);
    pushup(mid);
    return mid;
}

bool check(int x, int y, int z, int r) { return 1LL * x * x + 1LL * (y - z) * (y - z) <= 1LL * r * r; }

bool check(int p, int z, int r)
{
    bool flag = true;
    flag &= check(nodes[p].max_val[0], nodes[p].max_val[1], z, r);
    flag &= check(nodes[p].min_val[0], nodes[p].min_val[1], z, r);
    flag &= check(nodes[p].min_val[0], nodes[p].max_val[1], z, r);
    flag &= check(nodes[p].max_val[0], nodes[p].min_val[1], z, r);
    return flag;
}

int query(int p, int z, int r)
{
    if (p == 0)
        return 0;
    if (check(p, z, r))
        return nodes[p].sum;
    int ret = 0;
    if (check(nodes[p].d[0], nodes[p].d[1], z, r))
        ret++;
    for (int c = 0; c < 2; c++)
        if (nodes[p].ch[c])
        {
            bool flag = false;
            flag |= (nodes[p].min_val[1] > z + r);
            flag |= (nodes[p].max_val[1] < z - r);
            flag |= (nodes[p].min_val[0] > r);
            flag |= (nodes[p].max_val[0] < -r);
            if (!flag)
                ret += query(nodes[p].ch[c], z, r);
        }
    return ret;
}

int main()
{
    // freopen("ex_circle2.in", "r", stdin);
    n = read(), q = read(), srand(time(NULL));
    for (int i = 1; i <= n; i++)
        nodes[i].d[0] = read(), nodes[i].d[1] = read();
    groot = build(1, n);
    while (q--)
    {
        int z = read(), r = read();
        printf("%d\n", query(groot, z, r));
    }
    return 0;
}