// D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2020;
const double eps = 1e-10;

typedef long long ll;

int n, m, rk[MAX_N], pos[MAX_N];
ll S;

struct node
{
    ll x, y;
    node(ll x_ = 0, ll y_ = 0) : x(x_), y(y_) {}
    bool operator<(const node &rhs) const { return x < rhs.x || (x == rhs.x && y < rhs.y); }
    node operator-(const node &rhs) const { return node(x - rhs.x, y - rhs.y); }
    ll operator^(const node &rhs) const { return 1LL * x * rhs.y - y * rhs.x; }
} nodes[MAX_N];

struct segment
{
    int uid, vid;
    node vec;
    bool operator<(const segment &rhs) const { return (vec ^ rhs.vec) > 0; }
} segs[MAX_N * MAX_N];

int main()
{
    scanf("%d%lld", &n, &S), S <<= 1;
    for (int i = 1; i <= n; i++)
        scanf("%lld%lld", &nodes[i].x, &nodes[i].y);
    sort(nodes + 1, nodes + 1 + n);
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            segs[++m] = segment{i, j, nodes[j] - nodes[i]};
    sort(segs + 1, segs + 1 + m);
    for (int i = 1; i <= n; i++)
        rk[i] = pos[i] = i;
    for (int i = 1; i <= m; i++)
    {
        node nd = segs[i].vec;
        int uid = segs[i].uid, vid = segs[i].vid;
        if (rk[uid] > rk[vid])
            swap(uid, vid);
        int l = 1, r = rk[uid] - 1;
        while (l <= r)
        {
            int mid = (l + r) >> 1;
            ll curt_S = abs(nd ^ (nodes[pos[mid]] - nodes[pos[rk[uid]]]));
            if (curt_S == S)
            {
                printf("Yes\n%lld %lld\n%lld %lld\n%lld %lld\n", nodes[uid].x, nodes[uid].y, nodes[vid].x, nodes[vid].y, nodes[pos[mid]].x, nodes[pos[mid]].y);
                return 0;
            }
            else if (curt_S > S)
                l = mid + 1;
            else
                r = mid - 1;
        }
        swap(rk[uid], rk[vid]);
        swap(pos[rk[uid]], pos[rk[vid]]);
    }
    puts("No");
    return 0;
}