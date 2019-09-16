// CF762E.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 1e5 + 20, MAX_F = 1e4 + 200;

int n, k, tree[MAX_F], qtot;
ll ans;

struct station
{
    int x, r, f;
    bool operator<(const station &target) const { return r > target.r; }
} stats[MAX_N];

struct query
{
    int type, x, y, w;
    bool operator<(const query &q) { return x < q.x || (x == q.x && type < q.type); }
} queries[MAX_N * 5], tmp[MAX_N * 5];

bool compareByLowerBound(station a, station b) { return a.x - a.r < b.x - b.r; }

bool compareByUpperBound(station a, station b) { return a.x + a.r < b.x + b.r; }

inline int lowbit(int x) { return x & -x; }

void update(int x, int d)
{
    for (; x <= MAX_F - 1; x += lowbit(x))
        tree[x] += d;
}

int query(int x)
{
    int ans = 0;
    for (; x; x -= lowbit(x))
        ans += tree[x];
    return ans;
}

void clear(int x)
{
    for (; x <= MAX_F - 1; x += lowbit(x))
        tree[x] = 0;
}

void cdq(int l, int r)
{
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    cdq(l, mid), cdq(mid + 1, r);
    int ptr1 = l, ptr2 = mid + 1, tot = l - 1;
    while (ptr1 <= mid && ptr2 <= r)
        if (queries[ptr1] < queries[ptr2])
        {
            if (queries[ptr1].type == 0)
                update(queries[ptr1].y, 1);
            tmp[++tot] = queries[ptr1++];
        }
        else
        {
            if (queries[ptr2].type == 1)
                ans += query(queries[ptr2].y) * queries[ptr2].w;
            tmp[++tot] = queries[ptr2++];
        }
    while (ptr1 <= mid)
        tmp[++tot] = queries[ptr1++];
    while (ptr2 <= r)
    {
        if (queries[ptr2].type == 1)
            ans += query(queries[ptr2].y) * queries[ptr2].w;
        tmp[++tot] = queries[ptr2++];
    }
    for (int i = l; i <= r; i++)
    {
        if (queries[i].type == 0)
            clear(queries[i].y);
        queries[i] = tmp[i];
    }
}

int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d%d%d", &stats[i].x, &stats[i].r, &stats[i].f);
    sort(stats + 1, stats + 1 + n);
    for (int i = 1; i <= n; i++)
    {
        station st = stats[i];
        int x0 = st.x - st.r, x1 = st.x + st.r;
        int y0 = max(1, st.f - k), y1 = st.f + k;
        queries[++qtot] = {1, x0 - 1, y0 - 1, 1};
        queries[++qtot] = {1, x0 - 1, y1, -1};
        queries[++qtot] = {1, x1, y0 - 1, -1};
        queries[++qtot] = {1, x1, y1, 1};
        queries[++qtot] = {0, st.x, st.f, 0};
    }
    cdq(1, qtot);
    printf("%lld", ans);
    return 0;
}