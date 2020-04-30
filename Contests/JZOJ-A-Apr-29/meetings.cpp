// meetings.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e4 + 200;

int n, L, tree[MAX_N];
double pts[MAX_N];
pair<double, int> pdis[MAX_N];

struct node
{
    int w, x, d;
    bool operator<(const node &rhs) const { return x < rhs.x; }
} nodes[MAX_N];

void fileIO(string src)
{
    freopen((src + ".in").c_str(), "r", stdin);
    freopen((src + ".out").c_str(), "w", stdout);
}

inline int lowbit(int x) { return x & (-x); }

void update(int x, int d)
{
    for (; x <= n; x += lowbit(x))
        tree[x] += d;
}

int query(int x, int ret = 0)
{
    for (; x; x -= lowbit(x))
        ret += tree[x];
    return ret;
}

bool check(int mid)
{
    double time_point = mid / 2.0;
    for (int i = 1; i <= n; i++)
        pts[i] = nodes[i].x + 1.0 * nodes[i].d * time_point;
    sort(pts + 1, pts + 1 + n);
    double sum = 0, half = 0;
    for (int i = 1; i <= n; i++)
    {
        sum += nodes[i].w;
        if (pts[i] <= 0 || pts[i] >= L)
            half += nodes[i].w;
    }
    if (half >= sum / 2.0)
        return true;
    else
        return false;
}

int main()
{
    // fileIO("meetings");
    scanf("%d%d", &n, &L);
    for (int i = 1; i <= n; i++)
        scanf("%d%d%d", &nodes[i].w, &nodes[i].x, &nodes[i].d);
    sort(nodes + 1, nodes + 1 + n);
    int l = 0, r = L << 1, res;
    while (l <= r)
    {
        int mid = (0LL + l + r) >> 1;
        if (check(mid))
            res = mid, r = mid - 1;
        else
            l = mid + 1;
    }
    double time_point = res / 2.0;
    for (int i = 1; i <= n; i++)
        pdis[i] = make_pair(nodes[i].x + 1.0 * nodes[i].d * time_point, i);
    sort(pdis + 1, pdis + 1 + n);
    long long ans = 0;
    for (int i = 1; i <= n; i++)
        ans += i - query(pdis[i].second) - 1, update(pdis[i].second, 1);
    printf("%lld\n", ans);
    return 0;
}