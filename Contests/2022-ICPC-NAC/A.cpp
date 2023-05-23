// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1010;

int n, k, m, head[MAX_N], current, max_enc[MAX_N];
set<int> ans;
bool inQ[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].weight = weight;
    edges[current].nxt = head[src], head[src] = current++;
}

void solve(int pzero)
{
    queue<int> infected, infectious;
    infected.push(pzero);
    for (int day = 1; day <= k; day++)
    {
        // infected to infectious;
        while (!infected.empty())
            infectious.push(infected.front()), infected.pop();
        // infecting people;
        while (!infectious.empty())
        {
            int u = infectious.front();
            // go qurantine the other day;
            infectious.pop();
            for (int i = head[u]; i != -1; i = edges[i].nxt)
                if (edges[i].weight == day && max_enc[edges[i].to] <= day + 1)
                    infected.push(edges[i].to);
        }
    }
    while (!infected.empty())
    {
        int u = infected.front();
        infected.pop();
        ans.insert(u);
    }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d", &n, &k, &m);
    for (int i = 1, u, v, w; i <= m; i++)
    {
        scanf("%d%d%d", &u, &v, &w), addpath(u, v, w), addpath(v, u, w);
        max_enc[u] = max(max_enc[u], w);
        max_enc[v] = max(max_enc[v], w);
    }
    for (int i = 1; i <= n; i++)
        if (max_enc[i] <= 1)
            solve(i);
    printf("%lu\n", ans.size());
    while (!ans.empty())
        printf("%d\n", *ans.begin()), ans.erase(ans.begin());
    return 0;
}
