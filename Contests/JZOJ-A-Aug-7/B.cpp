// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 2000;

int n, m, pts[MAX_N];
struct interval
{
    int l, r;
    bool operator<(const interval &target) const { return l < target.l || (l == target.l && r < target.r); }
} ints[MAX_N];

struct compare
{
    bool operator()(interval a, interval b) { return a.r > b.r || (a.r == b.r && a.l > b.l); }
};

priority_queue<interval, vector<interval>, compare> q;

int main()
{
    /*
    freopen("dream.in", "r", stdin);
	freopen("dream.out", "w", stdout);
    */
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &ints[i].l, &ints[i].r);
    for (int i = 1; i <= m; i++)
        scanf("%d", &pts[i]);
    sort(ints + 1, ints + 1 + m);
    sort(pts + 1, pts + 1 + m);
    int ans = 0;
    for (int i = 1, cur = 1; i <= m; i++)
    {
        int u = pts[i];
        while (cur <= n && ints[cur].l <= u)
            q.push(ints[cur++]);
        while (!q.empty() && q.top().r < u)
            q.pop();
        if (!q.empty())
            ans++, q.pop();
    }
    printf("%d\n", ans);
    return 0;
}