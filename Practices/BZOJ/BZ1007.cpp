// BZ1007.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e4 + 200;
const double eps = 1e-8;

struct segment
{
    double a, b;
    int id;
    bool operator<(const segment &rhs) const { return a < rhs.a || (fabs(a - rhs.a) < eps && b < rhs.b); }
} segs[MAX_N];

int n, st[MAX_N], tail;
bool ans[MAX_N];

double getCross(segment &rhs1, segment &rhs2) { return double(rhs2.b - rhs1.b) / double(rhs1.a - rhs2.a); }

void insert(int id)
{
    while (tail != 0)
    {
        if (fabs(segs[st[tail]].a - segs[id].a) < eps)
            tail--;
        else if (tail > 1 && getCross(segs[st[tail - 1]], segs[id]) <= getCross(segs[st[tail]], segs[st[tail - 1]]))
            tail--;
        else
            break;
    }
    st[++tail] = id;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lf%lf", &segs[i].a, &segs[i].b), segs[i].id = i;
    sort(segs + 1, segs + 1 + n);
    for (int i = 1; i <= n; i++)
        insert(i);
    for (int i = 1; i <= tail; i++)
        ans[segs[st[i]].id] = true;
    for (int i = 1; i <= n; i++)
        if (ans[i])
            printf("%d ", i);
    return 0;
}
