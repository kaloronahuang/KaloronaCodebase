// CH4701.cpp
#include <bits/stdc++.h>
#define lowbit(x) (x & (-x))
using namespace std;
const int MAX_N = 1000006, POS_INF = 0x3f3f3f3f,
          NEG_INF = 0xcfcfcfcf;
int n, q, tree[MAX_N], max_tree, ans[MAX_N];
struct operation
{
    int type, x, y, id;
    bool operator<(const operation &opt) const
    {
        return x < opt.x || (x == opt.x && y < opt.y);
    }
} pre[MAX_N], line[MAX_N];
void update(int x, int d)
{
    while (x < max_tree)
        tree[x] = max(tree[x], d), x += lowbit(x);
}
int query(int x)
{
    int ans = NEG_INF;
    while (x)
        ans = max(ans, tree[x]), x -= lowbit(x);
    return ans;
}
void clear(int x)
{
    while (x < max_tree)
        tree[x] = NEG_INF, x += lowbit(x);
}
// process the interval [st, ed)
void process(int st, int ed, int offset, int dx, int dy)
{
    for (int i = st; i != ed; i += offset)
    {
        int y = (dy == 1) ? line[i].y : max_tree - line[i].y;
        int num = dx * line[i].x + dy * line[i].y;
        if (line[i].type == 1)
            update(y, num);
        else
            ans[line[i].id] = min(ans[line[i].id],
                                  num - query(y));
    }
    for (int i = st; i != ed; i += offset)
        if (line[i].type == 1)
            clear((dy == 1) ? line[i].y : max_tree - line[i].y);
}
void cdq(int l, int r)
{
    int mid = (l + r) >> 1;
    if (l < mid)
        cdq(l, mid);
    if (mid + 1 < r)
        cdq(mid + 1, r);
    int total_tmp = 0;
    for (int i = l; i <= r; i++)
        if ((pre[i].type == 1 && i <= mid) ||
            (pre[i].type == 2 && mid < i))
        {
            line[++total_tmp] = pre[i];
            line[total_tmp].id = i;
        }
    sort(line + 1, line + 1 + total_tmp);
    process(1, total_tmp + 1, 1, 1, 1);
    process(1, total_tmp + 1, 1, 1, -1);
    process(total_tmp, 0, -1, -1, -1);
    process(total_tmp, 0, -1, -1, 1);
}
int main()
{
    // initialize;
    memset(tree, 0xcf, sizeof(tree));
    memset(ans, 0x3f, sizeof(ans));
    // input;
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", &pre[i].x, &pre[i].y);
        pre[i].type = 1, max_tree = max(max_tree, pre[i].y);
    }
    for (int i = n + 1; i <= n + q; i++)
    {
        scanf("%d%d%d", &pre[i].type, &pre[i].x, &pre[i].y);
        max_tree = max(max_tree, pre[i].y);
    }
    max_tree++;
    cdq(1, n + q);
    for (int i = 1; i <= n + q; i++)
        if (pre[i].type == 2)
            printf("%d\n", ans[i]);
    return 0;
}