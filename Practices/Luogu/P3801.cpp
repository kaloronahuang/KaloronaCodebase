// P3801.cpp
#include <bits/stdc++.h>
#define lowbit(x) (x & -x)
using namespace std;
const int MAX_N = 101000;
int n, m, q, x_ctn[MAX_N], y_ctn[MAX_N], x_tree[MAX_N], y_tree[MAX_N], opt, tmpx, tmpy;
void add(int x, int d, int limit, int *tree)
{
    while (x <= limit)
        tree[x] += d, x += lowbit(x);
}
int sum(int x, int *tree)
{
    int ans = 0;
    while (x > 0)
        ans += tree[x], x -= lowbit(x);
    return ans;
}
void change(int x, int y)
{
    x_ctn[x] ^= 1, add(x, x_ctn[x] ? 1 : -1, n, x_tree);
    y_ctn[y] ^= 1, add(y, y_ctn[y] ? 1 : -1, m, y_tree);
}
int main()
{
    scanf("%d%d%d", &n, &m, &q);
    x_tree[0] = n, y_tree[0] = m;
    while (q--)
    {
        scanf("%d", &opt);
        if (opt == 1)
            scanf("%d%d", &tmpx, &tmpy), change(tmpx, tmpy);
        else
        {
            int x1, x2, y1, y2;
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            int s1 = sum(x2, x_tree) - sum(x1 - 1, x_tree);
            int s2 = sum(y2, y_tree) - sum(y1 - 1, y_tree);
            long long ans = 1LL * s1 * (y2 - y1 + 1) + 1LL * s2 * (x2 - x1 + 1) - 2LL * s1 * s2;
            printf("%lld\n", ans);
        }
    }
    return 0;
}