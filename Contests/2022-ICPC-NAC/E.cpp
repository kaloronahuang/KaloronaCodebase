// E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5050, MAX_V = 110, INF = 0x3f3f3f3f;

int n, head[MAX_N], current, vals[MAX_N], tag_bound, f[MAX_N][MAX_N], g[MAX_N][MAX_N], pbuffer[MAX_V];
vector<int> primes, tags, factors[MAX_N << 1];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void add_to_set(int x)
{
    for (int i = 2; 1LL * i * i <= x; i++)
        if (x % i == 0)
        {
            while (x % i == 0)
                x /= i;
            primes.push_back(i);
        }
    if (x > 1)
        primes.push_back(x);
}

void preprocess()
{
    for (int x = 2; x <= max(n << 1, MAX_V); x++)
    {
        int tmp = x;
        bool flag = true;
        vector<int> box;
        for (int p : primes)
            if (tmp % p == 0)
            {
                while (tmp % p == 0)
                    tmp /= p;
                box.push_back(p);
            }
        if (flag && tmp == 1)
        {
            tags.push_back(x);
            for (int v : box)
                factors[x].push_back(v);
        }
    }
}

void dfs(int u, int fa)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dfs(edges[i].to, u);
    memset(pbuffer, 0x3f, sizeof(pbuffer));
    for (int tag_id = 0; tag_id < tag_bound; tag_id++)
    {
        if (vals[u] != tags[tag_id])
            f[u][tag_id] = tags[tag_id];
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (edges[i].to != fa)
                f[u][tag_id] += g[edges[i].to][tag_id];
        for (int p : factors[tags[tag_id]])
            pbuffer[p] = min(pbuffer[p], f[u][tag_id]);
    }
    // update g;
    memset(g[u], 0x3f, sizeof(g[u]));
    for (int tag_id = 0; tag_id < tag_bound; tag_id++)
        for (int p : factors[tags[tag_id]])
            g[u][tag_id] = min(g[u][tag_id], pbuffer[p]);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n), primes.push_back(2);
    for (int i = 1; i <= n; i++)
        scanf("%d", &vals[i]), add_to_set(vals[i]);
    sort(primes.begin(), primes.end()), primes.erase(unique(primes.begin(), primes.end()), primes.end());
    preprocess(), tag_bound = tags.size();
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    dfs(1, 0);
    int ans = (n << 1);
    for (int i = 0; i < tag_bound; i++)
        ans = min(ans, f[1][i]);
    printf("%d\n", ans);
    return 0;
}
