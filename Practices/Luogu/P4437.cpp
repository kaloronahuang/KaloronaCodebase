// P4437.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 1e6 + 200;

int n, fa[MAX_N], head[MAX_N], mem[MAX_N], siz[MAX_N], current;
ll wi[MAX_N];
bool tag[MAX_N];

struct node
{
    int siz, id;
    ll val;
    bool operator<(const node &rhs) const { return val * rhs.siz > rhs.val * siz; }
};

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

int find(int x) { return mem[x] == x ? x : mem[x] = find(mem[x]); }

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

bool dfs(int u)
{
    tag[u] = true;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (tag[edges[i].to])
            return false;
        else if (!dfs(edges[i].to))
            return false;
    return true;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n), siz[0] = 1;
    for (int i = 1; i <= n; i++)
        scanf("%d", &fa[i]), mem[i] = i, siz[i] = 1, addpath(fa[i], i);
    if (head[0] == -1 || !dfs(0))
        puts("-1"), exit(0);
    priority_queue<node> pq;
    for (int i = 1; i <= n; i++)
        scanf("%lld", &wi[i]), pq.push(node{1, i, wi[i]});
    ll ans = 0;
    while (!pq.empty())
    {
        int curt;
        node u = pq.top();
        pq.pop();
        if (u.siz != siz[u.id])
            continue;
        mem[u.id] = curt = find(fa[u.id]), ans += 1LL * wi[u.id] * siz[curt];
        siz[curt] += siz[u.id], wi[curt] += wi[u.id];
        if (curt)
            pq.push(node{siz[curt], curt, wi[curt]});
    }
    printf("%lld\n", ans);
    return 0;
}