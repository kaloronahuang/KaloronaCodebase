// P2127.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 1e5 + 200;

struct node
{
    int val, id;
    bool operator<(const node &nd) const { return val < nd.val; }
} nodes[MAX_N];

int n;
bool vis[MAX_N];
ll ans;

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &nodes[i].val), nodes[i].id = i;
    sort(nodes + 1, nodes + 1 + n);
    for (int i = 1; i <= n; i++)
        if (vis[i] == false)
        {
            int p = i;
            ll tot = 0, sum = 0, min_val = 0x3f3f3f3f3f3f3f3f;
            while (vis[p] == false)
            {
                vis[p] = true, sum += nodes[p].val;
                if (min_val > nodes[p].val)
                    min_val = nodes[p].val;
                tot++, p = nodes[p].id;
            }
            ll val1 = sum + (tot - 2) * min_val;
            ll val2 = sum + nodes[1].val * (tot + 1) + min_val;
            ans += min(val1, val2);
        }
    printf("%lld", ans);
    return 0;
}