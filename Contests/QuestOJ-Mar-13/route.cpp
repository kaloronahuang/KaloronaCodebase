// route.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5055;

typedef long long ll;

int n;
char str[MAX_N];

struct point
{
    int x, y;
    point(const int x_ = 0, const int y_ = 0) : x(x_), y(y_) {}
    point operator+(const point &rhs) { return point(x + rhs.x, y + rhs.y); }
    point operator-(const point &rhs) { return point(x - rhs.x, y - rhs.y); }
    ll operator^(const point &rhs) const { return 1LL * x * rhs.y - 1LL * y * rhs.x; }
} pts[MAX_N];

int ans[MAX_N];
bool vis[MAX_N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &pts[i].x, &pts[i].y);
    scanf("%s", str + 1);
    point remote = point(1e9, 1e9);
    int remoteId;
    for (int i = 1; i <= n; i++)
        if (pts[i].x < remote.x || (pts[i].x == remote.x && pts[i].y < remote.y))
            remote = pts[i], remoteId = i;
    ans[1] = remoteId, vis[remoteId] = true;
    for (int i = 2; i <= n; i++)
    {
        int pt = -1;
        for (int j = 1; j <= n; j++)
            if (!vis[j])
            {
                if (pt == -1)
                    pt = j;
                else if ((str[i - 1] == 'L' && ((pts[j] - pts[remoteId]) ^ (pts[pt] - pts[remoteId])) > 0) ||
                         (str[i - 1] == 'R' && ((pts[j] - pts[remoteId]) ^ (pts[pt] - pts[remoteId])) < 0))
                    pt = j;
            }
        ans[i] = pt, vis[pt] = true, remoteId = pt;
    }
    for (int i = 1; i <= n; i++)
        printf("%d ", ans[i]);
    puts("");
    return 0;
}