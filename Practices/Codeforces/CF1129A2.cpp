// CF1129A2.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, m, req[MAX_N];
vector<int> G[MAX_N];

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v), G[u].push_back(v);
    for (int i = 1; i <= n; i++)
        if (G[i].empty())
            req[i] = 0;
        else
        {
            req[i] = (G[i].size() - 1) * n;
            int tmp = 1e9;
            for (auto &x : G[i])
                tmp = min(tmp, (x - i + n) % n);
            req[i] += tmp;
        }
    for (int i = 1; i <= n; i++)
    {
        int ret = 0;
        for (int bias = 0; bias < n; bias++)
        {
            int dst = (i + bias - 1) % n + 1;
            ret = max(ret, req[dst] == 0 ? 0 : req[dst] + bias);
        }
        printf("%d ", ret);
    }
    puts("");
    return 0;
}