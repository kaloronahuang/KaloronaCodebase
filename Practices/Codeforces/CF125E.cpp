// CF125E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5050, MAX_E = 1e5 + 200;

typedef long long ll;

int n, m, limit, mem[MAX_N];
ll ans;

struct edge
{
    int src, dst, id;
    ll weight;
    bool operator<(const edge &rhs) const { return weight < rhs.weight || (weight == rhs.weight && src > rhs.src); }
} edges[MAX_E], org[MAX_E];

vector<int> ansBox;

int find(int x) { return mem[x] == x ? x : mem[x] = find(mem[x]); }

int check(ll bias, bool output = false)
{
    for (int i = 1; i <= m; i++)
    {
        edges[i] = org[i];
        if (edges[i].src == 1 || edges[i].dst == 1)
            edges[i].weight += bias;
    }
    sort(edges + 1, edges + 1 + m), ans = 0;
    for (int i = 1; i <= n; i++)
        mem[i] = i;
    int ret = 0;
    for (int i = 1; i <= m; i++)
        if (find(edges[i].src) != find(edges[i].dst) && (edges[i].src != 1 || ret < limit))
        {
            ans += edges[i].weight, ret += (edges[i].src == 1 || edges[i].dst == 1);
            mem[find(edges[i].src)] = find(edges[i].dst);
            if (output)
                ansBox.push_back(edges[i].id);
        }
    return ret;
}

int main()
{
    scanf("%d%d%d", &n, &m, &limit);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%lld", &org[i].src, &org[i].dst, &org[i].weight);
        if (org[i].src > org[i].dst)
            swap(org[i].src, org[i].dst);
        org[i].id = i;
    }
    ll l = -1e9, r = 1e9;
    while (l < r)
    {
        ll mid = (0LL + l + r + 1) >> 1;
        if (check(mid) >= limit)
            l = mid;
        else
            r = mid - 1;
    }
    int ret = check(l, true);
    if (ret != limit || ansBox.size() != n - 1)
        puts("-1"), exit(0);
    printf("%lld\n", 1LL * ansBox.size());
    for (int u : ansBox)
        printf("%d ", u);
    puts("");
    return 0;
}