// C.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAX_N = 102000;
ll n, l, w;
struct node
{
    ll pos, cost;
    bool operator<(const node &nd) const { return pos < nd.pos; }
} nodes[MAX_N];
bool cmp(const node &n1, const node &n2) { return n1.cost < n2.cost; }
int main()
{
    scanf("%lld%lld%lld", &n, &l, &w);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &nodes[i].pos);
    sort(nodes + 1, nodes + 1 + n);
    int ans = nodes[n >> 1].pos;
    for (int i = 1; i <= n; i++)
        nodes[i].cost = abs(nodes[i].pos - ans);
    sort(nodes + 1, nodes + 1 + n, cmp);
    ans = 0;
    for (int i = 1; i <= n; i++)
        if (w >= nodes[i].cost)
            w -= nodes[i].cost, ans++;
        else
            break;
    printf("%lld", ans);
    return 0;
}