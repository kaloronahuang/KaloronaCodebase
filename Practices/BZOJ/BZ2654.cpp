// BZ2654.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 100100;

int n, m, white_req, ui[MAX_N], vi[MAX_N], wi[MAX_N], ci[MAX_N], mem[MAX_N];

struct edge
{
    int src, dst, weight, color;
    bool operator<(const edge &rhs) const { return weight < rhs.weight; }
} edges[MAX_N];

int find(int x) { return x == mem[x] ? x : mem[x] = find(mem[x]); }

pair<int, int> check(int mid)
{
    for (int i = 1; i <= n; i++)
        mem[i] = i;
    for (int i = 1; i <= m; i++)
    {
        edges[i].src = ui[i], edges[i].dst = vi[i], edges[i].weight = wi[i];
        edges[i].color = ci[i];
        if (edges[i].color == 0)
            edges[i].weight += mid;
    }
    sort(edges + 1, edges + 1 + m);
    int white_cnt = 0, val = 0;
    for (int i = 1; i <= m; i++)
        if (find(edges[i].src) != find(edges[i].dst))
            val += edges[i].weight, white_cnt += (!edges[i].color), mem[find(edges[i].src)] = find(edges[i].dst);
    return make_pair(white_cnt, val);
}

int main()
{
    scanf("%d%d%d", &n, &m, &white_req);
    for (int i = 1; i <= m; i++)
        scanf("%d%d%d%d", &ui[i], &vi[i], &wi[i], &ci[i]), ui[i]++, vi[i]++;
    // the range [-100, 100];
    int l = -105, r = 105, ans;
    while (l <= r)
    {
        int mid = (l + r) / 2;
        pair<int, int> res = check(mid);
        if (res.first >= white_req)
            l = mid + 1, ans = res.second - res.first * mid;
        else
            r = mid - 1;
    }
    printf("%d\n", ans);
    return 0;
}