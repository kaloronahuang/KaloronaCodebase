// A.cpp
#include <bits/stdc++.h>
#define ll long long
#define fraction long double

using namespace std;

const int MAX_N = 2e5 + 200;
const double eps = 1e-14;

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }

struct point
{
    long long x, y;
    fraction val;
    bool operator<(const point &pt) const { return val < pt.val; }
} pts[MAX_N];

int n, tmpx, tmpy;
long long ansP, ansQ;
fraction target_frac;

fraction calc(int x, int y) { return 1.0 * y - 1.0 * x * target_frac; }

int main()
{
    /*
    freopen("slope.in", "r", stdin);
    freopen("slope.out", "w", stdout);
    */
    scanf("%d%d%d", &n, &tmpx, &tmpy);
    target_frac = (1.0 * tmpx / tmpy);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &pts[i].x, &pts[i].y), pts[i].val = calc(pts[i].x, pts[i].y);
    sort(pts + 1, pts + 1 + n);
    ansP = 0, ansQ = 1;
    for (int i = 2; i <= n; i++)
    {
        fraction current = (1.0 * (pts[i].y - pts[i - 1].y) / (pts[i].x - pts[i - 1].x));
        if (fabs(current - target_frac) < fabs((1.0 * ansP / ansQ) - target_frac) || (fabs(current - target_frac) - fabs((1.0 * ansP / ansQ) - target_frac) < eps && current < (1.0 * ansP / ansQ)))
            ansP = pts[i].y - pts[i - 1].y, ansQ = pts[i].x - pts[i - 1].x;
        ll d = gcd(ansP, ansQ);
        ansP /= d, ansQ /= d;
    }
    printf("%lld/%lld", ansP, ansQ);
    return 0;
}