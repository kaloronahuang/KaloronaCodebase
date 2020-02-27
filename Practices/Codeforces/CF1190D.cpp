// CF1190D.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 4e5 + 200;

int n, nodes[MAX_N], upper;
bool vis[MAX_N];
vector<int> mp;
ll gans;

struct node
{
    int x, y;
    bool operator<(const node &rhs) const { return y > rhs.y || (y == rhs.y && x < rhs.x); }
} pts[MAX_N];

int ripe(int x) { return lower_bound(mp.begin(), mp.end(), x) - mp.begin() + 1; }

inline int lowbit(int x) { return x & (-x); }

void update(int x, int d)
{
    for (; x <= upper; x += lowbit(x))
        nodes[x] += d;
}

int query(int x, int ret = 0)
{
    for (; x; x -= lowbit(x))
        ret += nodes[x];
    return ret;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &pts[i].x, &pts[i].y), mp.push_back(pts[i].x), mp.push_back(pts[i].y);
    sort(mp.begin(), mp.end()), mp.erase(unique(mp.begin(), mp.end()), mp.end()), upper = mp.size();
    for (int i = 1; i <= n; i++)
        pts[i].x = ripe(pts[i].x), pts[i].y = ripe(pts[i].y);
    sort(pts + 1, pts + 1 + n);
    for (int ln = 1; ln <= n; ln++)
    {
        if (ln < n && pts[ln].y == pts[ln + 1].y)
        {
            if (!vis[pts[ln].x])
                update(pts[ln].x, 1);
            vis[pts[ln].x] = true;
            continue;
        }
        if (!vis[pts[ln].x])
            update(pts[ln].x, 1);
        vis[pts[ln].x] = true;
        int ptr = ln;
        while (pts[ptr - 1].y == pts[ln].y && ptr > 1)
            ptr--;
        ll tmp = 0;
        for (int i = ptr; i <= ln; i++)
        {
            // make the split ln;
            gans += 1LL * (query(upper) - query(pts[i].x - 1)) * (query(pts[i].x) - query(tmp));
            tmp = pts[i].x;
        }
    }
    printf("%lld\n", gans);
    return 0;
}