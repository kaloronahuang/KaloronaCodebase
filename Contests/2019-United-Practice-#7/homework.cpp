// homework.cpp
#include <bits/stdc++.h>

using namespace std;

inline int read()
{
    int X = 0, w = 0;
    char ch = 0;
    while (!isdigit(ch))
    {
        w |= ch == '-';
        ch = getchar();
    }
    while (isdigit(ch))
        X = (X << 3) + (X << 1) + (ch ^ 48), ch = getchar();
    return w ? -X : X;
}

const int MAX_N = 2e5 + 200;

struct point
{
    int x, y, val, id;
    bool operator<(const point &pt) const { return x < pt.x || (x == pt.x && y < pt.y); }
} pts[MAX_N];

int n, m, k, dp[MAX_N], tree[MAX_N << 1], upper;
vector<int> mpx, mpy;

inline int lowbit(int x) { return x & -x; }

void update(int x, int d)
{
    if (x == 0)
        return;
    for (; x <= upper; x += lowbit(x))
        tree[x] = max(tree[x], d);
}

int query(int x)
{
    int ans = 0;
    for (; x > 0; x -= lowbit(x))
        ans = max(tree[x], ans);
    return ans;
}

int main()
{
    freopen("homework.in", "r", stdin);
    freopen("homework.out", "w", stdout);
    n = read(), m = read(), k = read();
    for (int i = 1; i <= k; i++)
    {
        pts[i].x = read(), pts[i].y = read(), pts[i].val = read(), pts[i].id = i;
        mpx.push_back(pts[i].x), mpy.push_back(pts[i].y);
    }
    pts[k + 1] = point{n - 1, m - 1, 0, k + 1}, k++;
    mpx.push_back(n - 1), mpy.push_back(m - 1);
    sort(mpx.begin(), mpx.end()), sort(mpy.begin(), mpy.end());
    mpx.erase(unique(mpx.begin(), mpx.end()), mpx.end());
    mpy.erase(unique(mpy.begin(), mpy.end()), mpy.end());
    upper = mpy.size();
    for (int i = 1; i <= k; i++)
    {
        pts[i].x = lower_bound(mpx.begin(), mpx.end(), pts[i].x) - mpx.begin() + 1;
        pts[i].y = lower_bound(mpy.begin(), mpy.end(), pts[i].y) - mpy.begin() + 1;
    }
    sort(pts + 1, pts + 1 + k);
    for (int i = 1; i <= k; i++)
    {
        int ans = query(pts[i].y);
        dp[pts[i].id] = ans + pts[i].val;
        update(pts[i].y, dp[pts[i].id]);
    }
    printf("%d", dp[k]);
    return 0;
}