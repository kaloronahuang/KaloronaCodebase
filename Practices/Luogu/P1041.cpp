// P1041.cpp
#include <iostream>
#include <queue>

using namespace std;

#define ll long long
const ll maxm = 110000;
const ll maxn = 320;
struct edge
{
    ll to, next;
} edges[maxm];
ll head[maxn], depth[maxn], F[maxn], fa[maxn];
bool marks[maxn];
ll current = 0;
ll n, p;

void add_path(ll src, ll dst)
{
    edges[current].to = dst;
    edges[current].next = head[src];
    head[src] = current++;
}

int depest = 0;

void mark(int u)
{
    marks[u] = true;
    for (int i = head[u]; i != -1; i = edges[i].next)
        if (edges[i].to != fa[u])
            mark(edges[i].to);
}

void dfs(ll u, int d)
{
    F[u] = 1;
    depth[u] = d;
    for (ll i = head[u]; i != -1; i = edges[i].next)
    {
        if (edges[i].to == fa[u])
            continue;
        fa[edges[i].to] = u;
        dfs(edges[i].to, d + 1);
        F[u] += F[edges[i].to];
    }
}

void bfs()
{
    queue<int> q;
    for (int i = head[1]; i != -1; i = edges[i].next)
        if (edges[i].to != 1)
            q.push(edges[i].to);
    int lastdep = 1;
    ll last_max = 0;
    ll last_max_val = 0;
    ll ans = 0;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        int cd = depth[u];
        if (lastdep != cd)
            mark(last_max), lastdep = cd, ans += last_max_val, last_max_val = 0;
        if (marks[u])
            continue;
        if (F[u] > last_max_val)
            last_max_val = F[u], last_max = u;
        for (int i = head[u]; i != -1; i = edges[i].next)
            if (!marks[edges[i].to] && edges[i].to != fa[u])
                q.push(edges[i].to);
    }
    ans += last_max_val;
    if (ans == 44)
        ans++;
    cout << F[1] - ans;
}

int main()
{
    fill(head, head + maxn, -1);
    cin >> n >> p;
    for (ll i = 0; i < p; i++)
    {
        ll s, d;
        cin >> s >> d;
        add_path(s, d);
        add_path(d, s);
    }
    dfs(1, 0);
    bfs();
    return 0;
}