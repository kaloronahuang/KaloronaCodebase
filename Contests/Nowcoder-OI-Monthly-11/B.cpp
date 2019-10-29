// B.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 1e6 + 200;

ll tree[MAX_N];
int n;
vector<int> vec;

struct point
{
    int x, y, val;
    bool operator<(const point &nd) const { return x < nd.x || (x == nd.x && y < nd.y); }
} pts[MAX_N];

int getPos(int x) { return lower_bound(vec.begin(), vec.end(), x) - vec.begin() + 1; }

int lowbit(int x) { return x & (-x); }

void update(int x, ll d)
{
    for (; x < MAX_N; x += lowbit(x))
        tree[x] += d;
}

ll query(int x, ll ans = 0)
{
    for (; x; x -= lowbit(x))
        ans += tree[x];
    return ans;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d%d", &pts[i].x, &pts[i].y, &pts[i].val);
        vec.push_back(pts[i].x);
        vec.push_back(pts[i].y);
    }
    sort(vec.begin(), vec.end());
    for (int i = 1; i <= n; i++)
        pts[i].x = getPos(pts[i].x), pts[i].y = getPos(pts[i].y);
    sort(pts + 1, pts + 1 + n);
    ll ans = 0;
    for (int i = 1; i <= n; i++)
    {
        ans = max(ans, query(pts[i].y) + pts[i].val);
        update(pts[i].y, pts[i].val);
    }
    printf("%lld", ans);
    return 0;
}