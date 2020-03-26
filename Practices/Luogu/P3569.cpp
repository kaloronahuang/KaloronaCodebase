// P3569.cpp
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 4e5 + 200;

int n, ai[MAX_N][2], q;
bool nodes[MAX_N << 2][2][2];

inline char nc()
{
    static char buf[100000], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
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

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

inline void pushup(int p, int l, int r)
{
    nodes[p][0][0] = nodes[p][1][0] = nodes[p][0][1] = nodes[p][1][1] = false;
    for (register int a = 0; a < 2; a++)
        for (register int b = 0; b < 2; b++)
            for (register int c = 0; c < 2; c++)
                for (register int d = 0; d < 2; d++)
                    nodes[p][a][d] |= nodes[lson][a][c] && nodes[rson][b][d] && ai[mid][c] <= ai[mid + 1][b];
}

inline void update(int qx, int l, int r, int p)
{
    if (l == r)
        return;
    if (qx <= mid)
        update(qx, l, mid, lson);
    else
        update(qx, mid + 1, r, rson);
    pushup(p, l, r);
}

inline void build(int l, int r, int p)
{
    if (l == r)
    {
        nodes[p][0][0] = nodes[p][1][1] = true;
        return;
    }
    build(l, mid, lson), build(mid + 1, r, rson);
    pushup(p, l, r);
}

#undef mid
#undef rson
#undef lson

int main()
{
    n = read();
    for (register int i = 1; i <= n; i++)
        ai[i][0] = read(), ai[i][1] = read();
    q = read(), build(1, n, 1);
    while (q--)
    {
        int x = read(), y = read();
        swap(ai[x][0], ai[y][0]), swap(ai[x][1], ai[y][1]);
        update(x, 1, n, 1), update(y, 1, n, 1);
        puts(nodes[1][0][0] || nodes[1][0][1] || nodes[1][1][0] || nodes[1][1][1] ? "TAK" : "NIE");
    }
    return 0;
}