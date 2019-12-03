// YBT-OJ1672.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 200100;

struct node
{
    int ti, wi;
    bool operator<(const node &nd) const { return ti < nd.ti; }
} nodes[MAX_N];

int n;

int main()
{
    priority_queue<int> pq;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &nodes[i].ti, &nodes[i].wi);
    sort(nodes + 1, nodes + 1 + n);
    ll curt = 0, ans = 0;
    for (int i = 1; i <= n; i++)
    {
        if (curt < nodes[i].ti)
            ans += nodes[i].wi, pq.push(-nodes[i].wi), curt++;
        else if (!pq.empty() && nodes[i].wi > -pq.top())
            ans += pq.top() + nodes[i].wi, pq.pop(), pq.push(-nodes[i].wi);
    }
    printf("%lld", ans);
    return 0;
}