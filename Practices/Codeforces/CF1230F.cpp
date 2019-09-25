// CF1230F.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 1e5 + 200;

list<int> l2r[MAX_N];
list<int> r2l[MAX_N];

int n, indeg[MAX_N], outdeg[MAX_N], salaries[MAX_N], m, q;

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i <= m; i++)
    {
        scanf("%d%d", &u, &v);
        if (u < v)
            swap(u, v);
        r2l[u].push_back(v), l2r[v].push_back(u);
        outdeg[v]++, indeg[u]++;
    }
    for (int i = 1; i <= n; i++)
        salaries[i] = i;
    ll ans = 0;
    for (int i = 1; i <= n; i++)
        for (list<int>::iterator it = r2l[i].begin(); it != r2l[i].end(); it++)
            ans += indeg[*it];
    printf("%lld\n", ans);
    scanf("%d", &q);
    int days = 0;
    while (q--)
    {
        int u;
        days++, scanf("%d", &u), salaries[u] = n + days;
        ll flip_num = 0;
        for (list<int>::iterator it = l2r[u].begin(); it != l2r[u].end();)
            // if there is a edge needs flipping;
            if (salaries[u] > salaries[*it])
            {
                int id = *it;
                flip_num++;
                indeg[id]--;
                ans -= outdeg[id] - indeg[id];
                outdeg[id]++;
                list<int>::iterator backup = it;
                backup++, l2r[u].erase(it), it = backup;
                l2r[id].push_back(u);
            }
            else
                it++;
        ans += 1LL * (outdeg[u] - flip_num) * (indeg[u] + flip_num) - (1LL * indeg[u] * outdeg[u]);
        indeg[u] += flip_num, outdeg[u] -= flip_num;
        printf("%lld\n", ans);
    }
    return 0;
}