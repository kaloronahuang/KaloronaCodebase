// P3552.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 5001000, MAX_M = 9999991;

int n, m, limit, head[MAX_M], current, step;
ll S, T, ai[MAX_N];
char cmdlet[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_M];

queue<ll> q;

void remove(ll x)
{
    int u = x % MAX_M;
    edges[current].to = x, edges[current].nxt = head[u];
    head[u] = current++;
}

void add(ll x)
{
    int u = x % MAX_M;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to == x)
            return;
    edges[current].to = x, edges[current].nxt = head[u];
    head[u] = current++, q.push(x);
}

ll readHash()
{
    ll ret = 0;
    scanf("%s", cmdlet + 1);
    for (int i = 1; i <= n; i++)
        ret = 2LL * ret + cmdlet[i] - '0';
    return ret;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m), limit = n * m + 5;
    S = readHash(), T = readHash(), add(S);
    for (int i = 1; i <= m; i++)
        ai[i] = readHash(), remove(ai[i]);
    while (!q.empty() && step <= limit)
    {
        ll u = q.front();
        q.pop(), step++;
        if (u == T)
            return puts("TAK"), 0;
        for (int i = 0; i < n; i++)
            add(u ^ (1LL << i));
    }
    if (step <= limit)
        return puts("NIE"), 0;
    memset(head, -1, sizeof(head)), step = 0, current = 0;
    while (!q.empty())
        q.pop();
    for (int i = 1; i <= m; i++)
        remove(ai[i]);
    add(T);
    for (int i = 1; i <= m; i++)
        remove(ai[i]);
    while (!q.empty() && step <= limit)
    {
        ll u = q.front();
        q.pop(), step++;
        if (u == S)
            return puts("TAK"), 0;
        for (int i = 0; i < n; i++)
            add(u ^ (1LL << i));
    }
    return puts((step <= limit) ? "NIE" : "TAK"), 0;
}