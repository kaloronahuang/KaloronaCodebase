// POJ1733.cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
const int maxn = 102000;
int fa[maxn], dist[maxn], len, qlen;
vector<int> mapping;
struct quest
{
    int l, r, od;
} queries[maxn];
int getId(int x) { return lower_bound(mapping.begin(), mapping.end(), x) - mapping.begin(); }
int find(int x)
{
    if (fa[x] == x)
        return x;
    int root = find(fa[x]);
    dist[x] ^= dist[fa[x]];
    return fa[x] = root;
}
int main()
{
    scanf("%d%d", &len, &qlen);
    string tmp;
    for (int i = 1; i <= qlen; i++)
    {
        cin >> queries[i].l >> queries[i].r;
        cin >> tmp;
        queries[i].od = (tmp == "odd") ? 1 : 0;
        mapping.push_back(queries[i].l), mapping.push_back(queries[i].r);
    }
    sort(mapping.begin(), mapping.end());
    mapping.erase(unique(mapping.begin(), mapping.end()), mapping.end());
    len = mapping.size();
    for (int i = 0; i <= len; i++)
        fa[i] = i;
    for (int i = 1; i <= qlen; i++)
    {
        int x = getId(queries[i].l - 1), y = getId(queries[i].r);
        int p = find(x), q = find(y);
        if (p == q)
        {
            if ((dist[x] ^ dist[y]) != queries[i].od)
            {
                printf("%d", i - 1);
                return 0;
            }
        }
        else
            fa[p] = q, dist[p] = dist[x] ^ dist[y] ^ queries[i].od;
    }
    printf("%d", qlen);
    return 0;
}