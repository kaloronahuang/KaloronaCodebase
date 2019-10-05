// P3029.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e4 + 200;

int n, nodes[MAX_N << 2];
vector<int> mapping;

struct cow
{
    int x, d;
    bool operator<(const cow &c) const { return x < c.x; }
} cows[MAX_N];

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

void update(int qx, int l, int r, int p, int val)
{
    if (l == r)
        return (void)(nodes[p] = val);
    if (qx <= mid)
        update(qx, l, mid, lson, val);
    else
        update(qx, mid + 1, r, rson, val);
    nodes[p] = min(nodes[lson], nodes[rson]);
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &cows[i].x, &cows[i].d), mapping.push_back(cows[i].d), cows[i].x++;
    sort(mapping.begin(), mapping.end()), mapping.erase(unique(mapping.begin(), mapping.end()), mapping.end());
    for (int i = 1; i <= n; i++)
        cows[i].d = lower_bound(mapping.begin(), mapping.end(), cows[i].d) - mapping.begin() + 1;
    int ub = mapping.size();
    sort(cows + 1, cows + 1 + n);
    int ans = 0x7fffffff;
    for (int i = 1; i <= n; i++)
    {
        update(cows[i].d, 1, ub, 1, cows[i].x);
        if (nodes[1] != 0)
            ans = min(ans, abs(cows[i].x - nodes[1]));
    }
    printf("%d", ans);
    return 0;
}