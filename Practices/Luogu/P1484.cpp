// P1484.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 501000;

struct node
{
    ll val;
    int id;
    bool operator<(const node &nd) const { return val < nd.val; }
};

int n, k, seq[MAX_N], q[MAX_N], lft[MAX_N], rig[MAX_N];
ll val[MAX_N];
bool vanish[MAX_N];
priority_queue<node> pq;

int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &seq[i]);
        lft[i] = i - 1, rig[i] = i + 1;
        node nd = {seq[i], i};
        pq.push(nd), val[i] = seq[i];
    }
    rig[0] = 1, lft[n + 1] = n;
    ll ans = 0;
    while (k--)
    {
        while (vanish[pq.top().id])
            pq.pop();
        if (pq.top().val < 0)
            break;
        node u = pq.top();
        ans += u.val, pq.pop();
        // merge the three items;
        val[u.id] = val[lft[u.id]] + val[rig[u.id]] - val[u.id];
        vanish[lft[u.id]] = true, vanish[rig[u.id]] = true;
        lft[u.id] = lft[lft[u.id]], rig[u.id] = rig[rig[u.id]];
        rig[lft[u.id]] = u.id, lft[rig[u.id]] = u.id;
        pq.push(node{val[u.id], u.id});
    }
    printf("%lld", ans);
    return 0;
}