// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e5 + 200, MAX_K = 510;

int n, q, bit[MAX_K][MAX_K], matrix[MAX_K][MAX_K], od[MAX_N], o2[MAX_N];
int idx[MAX_N], xi[MAX_N], yi[MAX_N], ptot, pxi[MAX_N], pyi[MAX_N], sum[MAX_N];

struct query
{
    int x1, x2, y1, y2, k, ans;
} qs[MAX_N];

bool compareIndex(int a, int b) { return matrix[xi[a]][yi[a]] < matrix[xi[b]][yi[b]]; }

inline int lowbit(int x) { return x & (-x); }

inline void update(int id, int x, int d)
{
    for (int i = id; i <= n; i += lowbit(i))
        for (int j = x; j <= n; j += lowbit(j))
            bit[i][j] += d;
}

inline int query(int id, int x)
{
    int ans = 0;
    for (int i = id; i; i -= lowbit(i))
        for (int j = x; j; j -= lowbit(j))
            ans += bit[i][j];
    return ans;
}

void solve(int a, int b, int l, int r)
{
    if (a > b)
        return;
    if (l == r)
    {
        for (int i = a; i <= b; i++)
            qs[od[i]].ans = l;
        return;
    }
    int mid = (l + r) >> 1, A = a, B = b;
    for (int i = l; i <= mid; i++)
        update(pxi[i], pyi[i], 1);
    for (int i = a; i <= b; i++)
    {
        int idx = od[i];
        int tmp = query(qs[idx].x2, qs[idx].y2) - query(qs[idx].x1, qs[idx].y2) - query(qs[idx].x2, qs[idx].y1) + query(qs[idx].x1, qs[idx].y1);
        if (tmp + sum[idx] < qs[idx].k)
            sum[idx] += tmp, o2[B--] = idx;
        else
            o2[A++] = idx;
    }
    for (int i = l; i <= mid; i++)
        update(pxi[i], pyi[i], -1);
    for (int i = a; i <= b; i++)
        od[i] = o2[i];
    solve(a, B, l, mid), solve(A, b, mid + 1, r);
}

int main()
{
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            scanf("%d", &matrix[i][j]);
            idx[++ptot] = ptot;
            xi[ptot] = i, yi[ptot] = j;
        }
    sort(idx + 1, idx + 1 + ptot, compareIndex);
    for (int i = 1; i <= ptot; i++)
        pxi[i] = xi[idx[i]], pyi[i] = yi[idx[i]];
    for (int i = 1; i <= q; i++)
    {
        scanf("%d%d%d%d%d", &qs[i].x1, &qs[i].y1, &qs[i].x2, &qs[i].y2, &qs[i].k);
        qs[i].x1--, qs[i].y1--;
        od[i] = i;
    }
    solve(1, q, 1, ptot);
    for (int i = 1; i <= q; i++)
        printf("%d\n", matrix[pxi[qs[i].ans]][pyi[qs[i].ans]]);
    return 0;
}