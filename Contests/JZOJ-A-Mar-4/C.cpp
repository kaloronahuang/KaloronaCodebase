// C.cpp
#include <bits/stdc++.h>
#define ll long long
#define lowbit(x) (x & -x)
#define pr pair<int, int>
using namespace std;
const int MAX_N = 1e5 + 2000;
int n, m, tmpx, tmpy1, tot, tree[MAX_N << 2];
pr nodes[MAX_N << 2];
struct query
{
    int l, r, ans, id;
    bool operator<(const query &q) const { return id < q.id; }
} queries[MAX_N];
bool cmp(pr a, pr b) { return a.second < b.second; }
bool cmp2(query a, query b) { return a.r < b.r; }
void init(int l, int r)
{
    if (l == r)
    {
        nodes[++tot].first = l, nodes[tot].second = r;
        return;
    }
    nodes[++tot].first = l, nodes[tot].second = r;
    int mid;
    scanf("%d", &mid);
    init(l, mid), init(mid + 1, r);
}
void add(int x, int d)
{
    while (x <= n)
        tree[x] += d, x += lowbit(x);
}
ll sum(int x)
{
    ll ans = 0;
    while (x)
        ans += tree[x], x -= lowbit(x);
    return ans;
}
int main()
{
    scanf("%d%d", &n, &m);
    init(1, n);
    sort(nodes + 1, nodes + 1 + tot, cmp);
    for (int i = 1; i <= m; i++)
        scanf("%d%d", &queries[i].l, &queries[i].r), queries[i].id = i;
    sort(queries + 1, queries + 1 + m, cmp2);
    int cur = 1;
    for (int i = 1; i <= m; i++)
    {
        int xlimit = queries[i].r;
        while (nodes[cur].second <= xlimit && cur <= tot)
            add(nodes[cur].first, 1), cur++;
        queries[i].ans = sum(queries[i].r) - sum(queries[i].l - 1);
    }
    sort(queries + 1, queries + 1 + m);
    for (int i = 1; i <= m; i++)
        printf("%lld\n", 2 * (queries[i].r - queries[i].l + 1) - queries[i].ans);
    return 0;
}