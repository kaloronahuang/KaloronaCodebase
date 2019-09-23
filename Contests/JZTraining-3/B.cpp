// B.cpp
#include <bits/stdc++.h>
#define ll long long
#define pr pair<ll, int>

using namespace std;

const int MAX_N = 5e5 + 200, MAX_E = 2e6 + 200;

int head[MAX_N], n, m, current, S, T, mem[MAX_N];
ll dist[MAX_N];
bool vis[MAX_N];

namespace IO
{
const int MAXSIZE = 1 << 20;
char buf[MAXSIZE], *p1, *p2;
#define gc()                                                                 \
    (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, MAXSIZE, stdin), p1 == p2) \
         ? EOF                                                               \
         : *p1++)
inline int read()
{
    int x = 0, f = 1;
    char c = gc();
    while (!isdigit(c))
    {
        if (c == '-')
            f = -1;
        c = gc();
    }
    while (isdigit(c))
        x = x * 10 + (c ^ 48), c = gc();
    return x * f;
}
char pbuf[1 << 20], *pp = pbuf;
inline void push(const char &c)
{
    if (pp - pbuf == 1 << 20)
        fwrite(pbuf, 1, 1 << 20, stdout), pp = pbuf;
    *pp++ = c;
}
inline void write(int x)
{
    static int sta[35];
    int top = 0;
    do
    {
        sta[top++] = x % 10, x /= 10;
    } while (x);
    while (top)
        push(sta[--top] + '0');
}
} // namespace IO

using IO::read;

struct edge
{
    int from, to, nxt;
    ll weight, temp;
    bool operator<(const edge &target) const { return temp < target.temp; }
} edges[MAX_E], org[MAX_E];

int find(int x) { return x == mem[x] ? x : mem[x] = find(mem[x]); }

void addpath(int src, int dst, ll weight, ll temp)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, edges[current].temp = temp;
    head[src] = current++;
}

void shortest_path(int st)
{
    memset(dist, 0x3f, sizeof(dist));
    priority_queue<pr> pq;
    dist[st] = 0, pq.push(make_pair(0, st));
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        if (vis[u])
            continue;
        vis[u] = true;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (dist[edges[i].to] > dist[u] + edges[i].weight)
                dist[edges[i].to] = dist[u] + edges[i].weight, pq.push(make_pair(-dist[edges[i].to], edges[i].to));
    }
}

int main()
{
    freopen("running.in", "r", stdin);
    freopen("running.out", "w", stdout);
    memset(head, -1, sizeof(head));
    n = read(), m = read();
    for (int i = 1; i <= n; i++)
        mem[i] = i;
    for (int i = 1, u, v, a, b; i <= m; i++)
    {
        u = read(), v = read(), a = read(), b = read();
        org[i] = {u, v, 0, 1LL * a * b, a};
    }
    S = read(), T = read();
    sort(org + 1, org + 1 + m);
    int ans1 = 0x3f3f3f3f;
    for (int i = 1; i <= m; i++)
    {
        if (org[i].temp > ans1)
            break;
        addpath(org[i].from, org[i].to, org[i].weight, 0);
        addpath(org[i].to, org[i].from, org[i].weight, 0);
        if (find(org[i].from) != find(org[i].to))
            mem[find(org[i].from)] = find(org[i].to);
        if (find(S) == find(T))
            ans1 = org[i].temp;
    }
    shortest_path(S);
    printf("%d %lld", ans1, dist[T]);
    return 0;
}