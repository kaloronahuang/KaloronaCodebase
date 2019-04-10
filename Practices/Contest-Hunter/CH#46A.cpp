// CH#46A.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAX_N = 260000;
ll x_0, y_0, pL, rL, n;
int lft[MAX_N], rig[MAX_N], totblock, len, sign[MAX_N];
bool vis[MAX_N];
struct node
{
    ll x, y, m, p, r, dist;
} nodes[MAX_N];
ll pow2(ll bas) { return bas * bas; }
double getDist(node nd) { return pow2(nd.x - x_0) + pow2(nd.y - y_0); }
bool cmp(const node &nd1, const node &nd2) { return nd1.m < nd2.m; }
bool compare(const node &nd1, const node &nd2) { return nd1.dist < nd2.dist; }
void initialize()
{
    sort(nodes + 1, nodes + 1 + n, cmp);
    totblock = sqrt(n), len = n / totblock;
    for (int i = 1; i <= totblock; i++)
        lft[i] = (i - 1) * len + 1, rig[i] = i * len, sign[i] = nodes[rig[i]].m;
    if (rig[totblock] < n)
        lft[++totblock] = rig[totblock - 1] + 1, rig[totblock] = n, sign[totblock] = nodes[rig[totblock]].m;
    for (int i = 1; i <= totblock; i++)
        sort(nodes + lft[i], nodes + rig[i] + 1, compare);
}
int main()
{
    int answer = 0;
    scanf("%lld%lld%lld%lld%lld", &x_0, &y_0, &pL, &rL, &n);
    rL = rL * rL;
    for (int i = 1; i <= n; i++)
        scanf("%lld%lld%lld%lld%lld", &nodes[i].x, &nodes[i].y, &nodes[i].m, &nodes[i].p, &nodes[i].r),
            nodes[i].r = pow2(nodes[i].r), nodes[i].dist = getDist(nodes[i]);
    initialize();
    queue<node> q;
    nodes[0] = node{x_0, y_0, 0, pL, rL, 0};
    q.push(node{x_0, y_0, 0, pL, rL, 0});
    while (!q.empty())
    {
        node curt = q.front();
        q.pop();
        int idx = 0;
        for (int i = 1; i <= totblock; i++)
            if (sign[i] <= curt.p)
                idx = i;
            else
                break;
        for (int i = 1; i <= idx; i++)
            while (lft[i] <= rig[i] && curt.r >= nodes[lft[i]].dist)
            {
                if (vis[lft[i]] == false)
                    q.push(nodes[lft[i]]), answer++, vis[lft[i]] = true;
                lft[i]++;
            }
        idx++;
        if (totblock >= idx)
            for (int i = lft[idx]; i <= rig[idx]; i++)
                if (!vis[i] && curt.p >= nodes[i].m && curt.r >= nodes[i].dist)
                    vis[i] = true, q.push(nodes[i]), answer++;
    }
    printf("%d", answer);
    return 0;
}