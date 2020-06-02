// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 11;

int n, deg[MAX_N * MAX_N];
char mp[MAX_N][MAX_N];
bool vis[MAX_N * MAX_N];
vector<int> G[MAX_N * MAX_N];

namespace bruteForce
{

    bool dfs(int u, int fa)
    {
        if (vis[u])
            return false;
        vis[u] = true;
        for (int v : G[u])
            if (v != fa && !dfs(v, u))
                return false;
        return true;
    }

    int getId(int x, int y) { return (x - 1) * (n + 1) + y; }

    int handler()
    {
        auto addpath = [](int x, int y) { G[x].push_back(y), G[y].push_back(x), deg[x]++, deg[y]++; };
        for (int stat = 0; stat < (1 << (n * n)); stat++)
        {
            for (int i = 1; i <= n + 1; i++)
                for (int j = 1; j <= n + 1; j++)
                {
                    int id = getId(i, j);
                    G[id].clear(), vis[id] = false, deg[id] = 0;
                }
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                {
                    int id = (i - 1) * n + j - 1;
                    if (stat & (1 << id))
                        addpath(getId(i, j), getId(i + 1, j + 1));
                    else
                        addpath(getId(i + 1, j), getId(i, j + 1));
                }
            bool flag = true;
            for (int i = 1; i <= n + 1 && flag; i++)
                for (int j = 1; j <= n + 1 && flag; j++)
                    if (mp[i][j] != '.' && mp[i][j] - '0' != deg[getId(i, j)])
                        flag = false;
            for (int i = 1; i <= n && flag; i++)
                for (int j = 1; j <= n && flag; j++)
                    if (vis[getId(i, j)] == false && !dfs(getId(i, j), 0))
                        flag = false;
            if (flag)
            {
                for (int i = 1; i <= n; i++, putchar('\n'))
                    for (int j = 1; j <= n; j++)
                    {
                        int id = (i - 1) * n + j - 1;
                        if (stat & (1 << id))
                            putchar('\\');
                        else
                            putchar('/');
                    }
                return 0;
            }
        }
        return 0;
    }

} // namespace bruteForce

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n + 1; i++)
        scanf("%s", mp[i] + 1);
    if (n <= 5)
        return bruteForce::handler();
    return 0;
}