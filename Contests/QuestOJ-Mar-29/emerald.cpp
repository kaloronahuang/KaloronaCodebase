// emerald.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, q, levels[MAX_N], opts[MAX_N];
char cmdlet[MAX_N];

namespace bruteForce
{

int nodes[100], dir[MAX_N];

inline int lowbit(int x) { return x & (-x); }

void update(int x, int d)
{
    for (; x < 100; x += lowbit(x))
        nodes[x] += d;
}

int query(int x, int ret = 0)
{
    for (; x; x -= lowbit(x))
        ret += nodes[x];
    return ret;
}

int calc()
{
    int ret = 0;
    memset(nodes, 0, sizeof(nodes));
    for (int i = 1; i <= n; i++)
    {
        if (opts[i] == 1)
            ret += query(99) - query(levels[i]) > 0;
        else
            update(levels[i], 1);
        if (dir[i] == 0)
            memset(nodes, 0, sizeof(nodes));
    }
    for (int i = n; i >= 1; i--)
    {
        if (dir[i] == 1)
            memset(nodes, 0, sizeof(nodes));
        if (opts[i] == 1)
            ret += query(99) - query(levels[i]) > 0;
        else
            update(levels[i], 1);
    }
    return ret;
}

int subtaskHandler()
{
    while (q--)
    {
        int x, y;
        scanf("%s%d%d", cmdlet + 1, &x, &y);
        if (cmdlet[1] == 'U')
            levels[x] = y + 1;
        else
            for (int i = x; i <= y; i++)
                dir[i] = !dir[i];
        printf("%d\n", calc());
    }
    return 0;
}

} // namespace bruteForce

namespace updateOnly
{

struct SegmentTree
{

    int nodes[MAX_N << 2][78];

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

    void pushup(int p)
    {
        for (int i = 1; i <= 77; i++)
            nodes[p][i] = nodes[lson][i] + nodes[rson][i];
    }

    void update(int qx, int l, int r, int p, int val)
    {
        if (l == r)
        {
            for (int i = 1; i <= val; i++)
                nodes[p][i] = 1;
            for (int i = val + 1; i <= 77; i++)
                nodes[p][i] = 0;
            return;
        }
        if (qx <= mid)
            update(qx, l, mid, lson, val);
        else
            update(qx, mid + 1, r, rson, val);
        pushup(p);
    }

    int query(int ql, int qr, int l, int r, int p, int threshold)
    {
        if (ql <= l && r <= qr)
            return nodes[p][threshold];
        int ret = 0;
        if (ql <= mid)
            ret += query(ql, qr, l, mid, lson, threshold);
        if (mid < qr)
            ret += query(ql, qr, mid + 1, r, rson, threshold);
        return ret;
    }
} tr[2];

int pre[MAX_N];

int subtaskHandler()
{
    for (int i = 1; i <= n; i++)
        tr[opts[i]].update(i, 1, n, 1, levels[i]), pre[i] = pre[i - 1] + opts[i];
    int ans = 0;
    for (int i = 1; i <= n; i++)
        if (opts[i] == 1)
            ans += tr[0].query(i + 1, n, 1, n, 1, levels[i] + 1) > 0;
    while (q--)
    {
        int i, r;
        scanf("%s%d%d", cmdlet + 1, &i, &r);
        if (opts[i] == 1)
        {
            ans -= tr[0].query(i + 1, n, 1, n, 1, levels[i] + 1) > 0;
            levels[i] = r + 1, tr[1].update(i, 1, n, 1, levels[i]);
            ans += tr[0].query(i + 1, n, 1, n, 1, levels[i] + 1) > 0;
        }
        else
        {
            ans -= pre[i - 1] - tr[1].query(1, i - 1, 1, n, 1, levels[i]);
            levels[i] = r + 1, tr[0].update(i, 1, n, 1, levels[i]);
            ans += pre[i - 1] - tr[1].query(1, i - 1, 1, n, 1, levels[i]);
        }
        printf("%d\n", ans);
    }
    return 0;
}

} // namespace updateOnly

int main()
{
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
        scanf("%d%s", &levels[i], cmdlet + 1), opts[i] = cmdlet[1] == 'A', levels[i]++;
    if (max(n, q) <= 1000)
        return bruteForce::subtaskHandler();
    return updateOnly::subtaskHandler();
}