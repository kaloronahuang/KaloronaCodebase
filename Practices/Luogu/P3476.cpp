// P3476.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3030;

typedef long long ll;

int n;

struct point
{
    int x, y;

    bool operator<(const point &rhs) const { return x < rhs.x || (x == rhs.x && y < rhs.y); }
} pts[MAX_N], tmp[MAX_N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &pts[i].x, &pts[i].y);
    sort(pts + 1, pts + 1 + n);
    ll ans = 0;
    for (int i = 1; i <= n - 2; i++)
    {
        int tot = 0;
        for (int j = i + 1; j <= n; j++)
            tmp[++tot] = point{pts[j].x - pts[i].x, pts[j].y - pts[i].y};
        sort(tmp + 1, tmp + 1 + tot, [](const point &rhs1, const point &rhs2) { return 1LL * rhs1.x * rhs2.y - 1LL * rhs1.y * rhs2.x < 0; });
        ll sumx = 0, sumy = 0;
        for (int j = 1; j <= tot; j++)
            sumx += tmp[j].x, sumy += tmp[j].y;
        for (int j = tot; j >= 1; j--)
        {
            sumx -= tmp[j].x, sumy -= tmp[j].y;
            ans += 1LL * tmp[j].x * sumy - 1LL * tmp[j].y * sumx;
        }
    }
    if (ans & 1)
        printf("%lld.5\n", ans >> 1);
    else
        printf("%lld.0\n", ans >> 1);
    return 0;
}