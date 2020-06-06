// CF1361A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e5 + 200;

int n, m, pi[MAX_N], idx[MAX_N], val[MAX_N];
vector<int> G[MAX_N];

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v), G[u].push_back(v), G[v].push_back(u);
    for (int i = 1; i <= n; i++)
        scanf("%d", &pi[i]), idx[i] = i;
    sort(idx + 1, idx + 1 + n, [](const int &rhs1, const int &rhs2) { return pi[rhs1] < pi[rhs2]; });
    bool flag = true;
    for (int i = 1; i <= n; i++)
    {
        int u = idx[i];
        vector<int> vec;
        for (int v : G[u])
        {
            vec.push_back(val[v]);
            if (val[v] == pi[u])
                puts("-1"), exit(0);
        }
        sort(vec.begin(), vec.end()), vec.erase(unique(vec.begin(), vec.end()), vec.end());
        flag &= (upper_bound(vec.begin(), vec.end(), pi[u]) - vec.begin() - (!vec.empty() && vec[0] == 0) == pi[u] - 1);
        val[u] = pi[u];
    }
    if (!flag)
        puts("-1"), exit(0);
    for (int i = 1; i <= n; i++)
        printf("%d ", idx[i]);
    puts("");
    return 0;
}