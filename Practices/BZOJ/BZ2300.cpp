// BZ2300.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 200100;
const double eps = 1e-8;

int n, m, q, ansTot, ox, oy;
double cost;
bool tag[MAX_N];
pair<int, int> pts[MAX_N];

struct node
{
    int x, y;
    double angle;
} O;

struct query
{
    int opt, id;
} queries[MAX_N];

double getDist(node A, node B) { return hypot(abs(A.x - B.x), abs(A.y - B.y)); }

double cross(node A, node B) { return A.x * B.y - A.y * B.x; }

node operator-(node A, node B) { return node{A.x - B.x, A.y - B.y, 0}; }

bool operator<(const node &A, const node &B) { return fabs(A.angle - B.angle) < eps ? getDist(O, A) < getDist(O, B) : A.angle < B.angle; }

set<node> convexHull;
double ansBox[MAX_N];

typedef set<node>::iterator It;

It previous(It curt) { return curt == convexHull.begin() ? (--convexHull.end()) : (--curt); }

It succ(It curt) { return (++curt) == convexHull.end() ? convexHull.begin() : curt; }

void insert(node u)
{
    It nxt = convexHull.lower_bound(u);
    if (nxt == convexHull.end())
        nxt = convexHull.begin();
    It pre = previous(nxt);
    if (cross(u - *pre, *nxt - u) <= 0)
        return;
    convexHull.insert(u);
    It curt = convexHull.find(u), i, j;
    i = previous(curt), j = previous(i);
    pre = previous(curt), nxt = succ(curt);
    cost += getDist(*curt, *pre) + getDist(*curt, *nxt) - getDist(*pre, *nxt);
    while (cross(*i - *j, *curt - *i) <= 0)
    {
        cost -= getDist(*curt, *i);
        cost -= getDist(*i, *j);
        cost += getDist(*curt, *j);
        convexHull.erase(i), i = j, j = previous(j);
    }
    i = succ(curt), j = succ(i);
    while (cross(*i - *curt, *j - *i) <= 0)
    {
        cost -= getDist(*curt, *i);
        cost -= getDist(*i, *j);
        cost += getDist(*curt, *j);
        convexHull.erase(i), i = j, j = succ(j);
    }
}

int main()
{
    scanf("%d%d%d%d", &n, &ox, &oy, &m), ox *= 3, oy *= 3, n *= 3;
    for (int i = 1; i <= m; i++)
        scanf("%d%d", &pts[i].first, &pts[i].second), pts[i].first *= 3, pts[i].second *= 3;
    scanf("%d", &q);
    for (int i = 1; i <= q; i++)
    {
        scanf("%d", &queries[i].opt);
        if (queries[i].opt == 1)
            scanf("%d", &queries[i].id), tag[queries[i].id] = true;
    }
    O = node{(n + ox) / 3, oy / 3, 0};
    node p1 = node{0, 0, atan2(0 - O.y, 0 - O.x)};
    node p2 = node{n, 0, atan2(0 - O.y, n - O.x)};
    node p3 = node{ox, oy, atan2(oy - O.y, ox - O.x)};
    convexHull.insert(p1), convexHull.insert(p2), cost += getDist(p2, p3), convexHull.insert(p3), cost += getDist(p1, p3);
    for (int i = 1; i <= m; i++)
        if (!tag[i])
            insert(node{pts[i].first, pts[i].second, atan2(pts[i].second - O.y, pts[i].first - O.x)});
    for (int i = q; i >= 1; i--)
        if (queries[i].opt == 1)
            insert(node{pts[queries[i].id].first, pts[queries[i].id].second, atan2(pts[queries[i].id].second - O.y, pts[queries[i].id].first - O.x)});
        else
            ansBox[++ansTot] = cost;
    for (int i = ansTot; i >= 1; i--)
        printf("%.2lf\n", ansBox[i] / 3.0);
    return 0;
}