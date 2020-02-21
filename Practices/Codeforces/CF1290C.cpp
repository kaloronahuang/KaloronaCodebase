// CF1290C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e5 + 200, INF = 0x3f3f3f3f;

int n, ktot, fa[MAX_N], gans;
char str[MAX_N];
vector<int> aff[MAX_N];

struct node
{
    int l, r, val;
    int read() { return min(l, r); }
    void operator+=(const node &rhs) { l = min(INF, l + rhs.l), r = min(INF, r + rhs.r); }
} nodes[MAX_N];

pair<int, int> find(int u)
{
    if (fa[u] < 0)
        return make_pair(u, 0);
    else
    {
        pair<int, int> res = find(fa[u]);
        fa[u] = res.first, nodes[u].val ^= res.second;
        return make_pair(fa[u], nodes[u].val);
    }
}

int main()
{
    scanf("%d%d%s", &n, &ktot, str + 1);
    for (int i = 1, tot; i <= ktot; i++)
    {
        fa[i] = -1, nodes[i] = node{1, 0, 0}, scanf("%d", &tot);
        for (int j = 1, val; j <= tot; j++)
            scanf("%d", &val), aff[val].push_back(i);
    }
    for (int i = 1; i <= n; i++)
    {
        int color = (str[i] - '0') ^ 1;
        if (aff[i].size() == 1)
        {
            pair<int, int> u = find(aff[i][0]);
            gans -= nodes[u.first].read();
            nodes[u.first] += node{(u.second == color) * INF, (u.second != color) * INF};
            gans += nodes[u.first].read();
        }
        else if (aff[i].size() == 2)
        {
            pair<int, int> u = find(aff[i][0]), v = find(aff[i][1]);
            if (u.first != v.first)
            {
                gans -= nodes[u.first].read() + nodes[v.first].read();
                if (fa[u.first] > fa[v.first])
                    swap(u, v);
                if (u.second ^ v.second ^ color)
                    nodes[v.first].val = 1, swap(nodes[v.first].l, nodes[v.first].r);
                fa[u.first] += fa[v.first], fa[v.first] = u.first, nodes[u.first] += nodes[v.first];
                gans += nodes[u.first].read();
            }
        }
        printf("%d\n", gans);
    }
    return 0;
}