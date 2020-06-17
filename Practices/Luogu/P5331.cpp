// P5331.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200, INF = 0x3f3f3f3f;
typedef long long ll;

int head[MAX_N], current, n, W, ai[MAX_N], start_pos, end_pos, flow[MAX_N], pre[MAX_N], ptot;
int stk[MAX_N];
ll dist[MAX_N];
bool vis[MAX_N];

struct edge
{
    int to, nxt, weight, cost;
} edges[MAX_N << 1];

void addpath(int src, int dst, int weight, int cost)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, edges[current].cost = cost;
    head[src] = current++;
}

void addtube(int src, int dst, int weight, int cost)
{
    addpath(src, dst, weight, cost);
    addpath(dst, src, 0, -cost);
}

bool spfa()
{
    memset(dist, 0x3f, sizeof(ll) * (ptot + 10)), memset(vis, false, sizeof(bool) * (ptot + 10));
    queue<int> q;
    q.push(start_pos), vis[start_pos] = true, dist[start_pos] = 0, flow[start_pos] = INF;
    while (!q.empty())
    {
        ll u = q.front();
        q.pop(), vis[u] = false;
        for (ll i = head[u]; i != -1; i = edges[i].nxt)
            if (edges[i].weight > 0 && dist[edges[i].to] > dist[u] + edges[i].cost)
            {
                dist[edges[i].to] = dist[u] + edges[i].cost;
                flow[edges[i].to] = min(flow[u], edges[i].weight);
                pre[edges[i].to] = i;
                if (!vis[edges[i].to])
                    vis[edges[i].to] = true, q.push(edges[i].to);
            }
    }
    return dist[end_pos] != 0x3f3f3f3f3f3f3f3f;
}

ll mcmf()
{
    ll max_flow = 0, min_cost = 0;
    while (spfa())
    {
        ll p = end_pos, i = pre[end_pos];
        max_flow += flow[end_pos], min_cost += 1LL * flow[end_pos] * dist[end_pos];
        while (p != start_pos)
        {
            edges[i].weight -= flow[end_pos], edges[i ^ 1].weight += flow[end_pos];
            p = edges[i ^ 1].to, i = pre[p];
        }
    }
    return min_cost;
}

void solve(int l, int r)
{
	if (l == r)
		return;
	int mid = (l + r) >> 1, tot = 0;
	solve(l, mid), solve(mid + 1, r);
	for (int i = l; i <= r; i++)
		stk[++tot] = ai[i];
	sort(stk + 1, stk + 1 + tot), tot = unique(stk + 1, stk + 1 + tot) - stk - 1;
	for (int i = 1; i < tot; i++)
	{
		addtube(ptot + i, ptot + i + 1, INF, stk[i + 1] - stk[i]);
		addtube(ptot + i + 1, ptot + i, INF, stk[i + 1] - stk[i]);
	}
	for (int i = l; i <= r; i++)
	{
		int pos = lower_bound(stk + 1, stk + 1 + tot, ai[i]) - stk;
		if (i <= mid)
			addtube(ptot + pos, i + n, 1, 0);
		else
			addtube(i, ptot + pos, 1, 0);
	}
	ptot += tot;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &W), start_pos = 2 * n + 1, end_pos = ptot = start_pos + 1;
	for (int i = 1; i <= n; i++)
		scanf("%d", &ai[i]), addtube(start_pos, i, 1, 0), addtube(i + n, end_pos, 1, 0), addtube(i, end_pos, 1, W);
	solve(1, n);
    printf("%lld\n", mcmf());
    return 0;
}
