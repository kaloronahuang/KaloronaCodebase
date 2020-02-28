// LOJ3113.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int T, n, m, head[MAX_N], current, deg[MAX_N], orgdeg[MAX_N], delseq[MAX_N], indseq[MAX_N], dtot, itot;
bool vis[MAX_N], color[MAX_N];

typedef pair<int, int> pii;

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

inline char nc()
{
    static char buf[100000], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
}

int read()
{
    int x = 0, f = 1;
    char ch = nc();
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = nc();
    }
    while (isdigit(ch))
        x = (x << 3) + (x << 1) + ch - '0', ch = nc();
    return x * f;
}

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

int main()
{
    T = read();
    while (T--)
    {
        memset(head, -1, sizeof(head)), current = 0;
        memset(orgdeg, 0, sizeof(orgdeg));
        n = read(), m = read();
        for (int i = 1, u, v; i <= m; i++)
            u = read(), v = read(), addpath(u, v), addpath(v, u), orgdeg[u]++, orgdeg[v]++;
        memcpy(deg, orgdeg, sizeof(deg));
        priority_queue<pii> pq;
        for (int i = 1; i <= n; i++)
            pq.push(make_pair(-deg[i], i));
        memset(vis, false, sizeof(vis)), dtot = 0;
        int peak = 0, peak_pos = 0;
        while (!pq.empty())
        {
            int cdeg = -pq.top().first, u = pq.top().second;
            pq.pop();
            if (vis[u])
                continue;
            if (cdeg > peak)
                peak = cdeg, peak_pos = dtot;
            vis[u] = true, delseq[++dtot] = u;
            for (int i = head[u]; i != -1; i = edges[i].nxt)
                if (!vis[edges[i].to])
                    deg[edges[i].to]--, pq.push(make_pair(-deg[edges[i].to], edges[i].to));
        }
        memset(vis, false, sizeof(vis)), itot = 0;
        memcpy(deg, orgdeg, sizeof(deg));
        for (int i = 1; i <= n; i++)
            pq.push(make_pair(-deg[i], i));
        while (!pq.empty())
        {
            int cdeg = -pq.top().first, u = pq.top().second;
            pq.pop();
            if (vis[u])
                continue;
            vis[u] = true, indseq[++itot] = u;
            if (cdeg != deg[u])
                continue;
            for (int i = head[u]; i != -1; i = edges[i].nxt)
                if (!vis[edges[i].to])
                {
                    vis[edges[i].to] = true;
                    for (int j = head[edges[i].to]; j != -1; j = edges[j].nxt)
                        if (!vis[edges[j].to])
                            --deg[edges[j].to], pq.push(make_pair(-deg[edges[j].to], edges[j].to));
                }
        }
        memset(color, false, sizeof(color));
        for (int i = 1; i <= peak_pos; i++)
            color[delseq[i]] = true;
        printf("%d ", n - peak_pos);
        for (int i = 1; i <= n; i++)
            if (!color[i])
                printf("%d ", i);
        puts("");
        printf("%d ", itot);
        for (int i = 1; i <= itot; i++)
            printf("%d ", indseq[i]);
        puts("");
    }
    return 0;
}