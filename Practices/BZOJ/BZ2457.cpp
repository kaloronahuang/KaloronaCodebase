// BZ2457.cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 2e5 + 100;
int n;
struct node
{
    int val, idx;
    bool operator<(const node &nd) const
    {
        return val < nd.val || (val == nd.val && idx < nd.idx);
    }
} nodes[maxn];
int a[maxn], b[maxn];
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &nodes[i].val), nodes[i].idx = i;
    sort(nodes + 1, nodes + 1 + n);
    int cnt = 0;
    for (int i = 1; i <= n; i++)
        if (i == 1 || nodes[i].val != nodes[i - 1].val)
            a[cnt] = nodes[i - 1].idx, b[++cnt] = nodes[i].idx;
    a[cnt] = nodes[n].idx;
    bool opt = true;
    int last = 2e9, ans = 0;
    for (int i = 1; i <= cnt; i++)
        if (!opt)
            if (last > a[i])
                last = b[i];
            else
                last = a[i], opt = true;
        else if (last < b[i])
            last = a[i];
        else
            opt = false, ans++, last = b[i];
    printf("%d", ans);
    return 0;
}