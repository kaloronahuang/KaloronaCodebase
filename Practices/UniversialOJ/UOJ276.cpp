// UOJ276.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e4 + 200;

typedef long long ll;

int n, head[MAX_N], current, siz[MAX_N], tail, start_pos;
ll std_val, ans = 1e18;
bool tag[MAX_N];

struct edge
{
    int to, nxt;
    ll weight;
} edges[MAX_N << 1];

struct data
{
    ll dep, dist, org;
    bool operator<(const data &rhs) const { return dist < rhs.dist; }
} q[MAX_N];

void addpath(int src, int dst, ll weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

int root, root_val;

void getRoot(int u, int fa, int capacity)
{
    int max_siz = 0;
    siz[u] = 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa && !tag[edges[i].to])
        {
            getRoot(edges[i].to, u, capacity), siz[u] += siz[edges[i].to];
            max_siz = max(max_siz, siz[edges[i].to]);
        }
    if (max(max_siz, capacity - siz[u]) < root_val)
        root_val = max(max_siz, capacity - siz[u]), root = u;
}

int getRoot(int entry_point, int capacity) { return root_val = 0x3f3f3f3f, root = 0, getRoot(entry_point, 0, capacity), root; }

void dfs(int u, int fa, ll dep, ll dist, int org)
{
    q[++tail] = data{dep, dist, org};
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa && !tag[edges[i].to])
            dfs(edges[i].to, u, dep + 1, dist + edges[i].weight, org);
}

pair<ll, ll> fir, sec;

void update(pair<ll, ll> curt)
{
    if (curt.first < sec.first)
    {
        if (curt.first < fir.first)
        {
            if (curt.second != fir.second)
                swap(fir, sec);
            fir = curt;
        }
        else if (curt.second != fir.second)
            sec = curt;
    }
}

bool check_positive(ll mid)
{
    fir = sec = make_pair(1LL << 60, 0);
    for (int i = start_pos, ptr = start_pos - 1; i <= tail; i++)
    {
        while (ptr >= 1 && q[i].dist + q[ptr].dist >= 0)
            update(make_pair(q[ptr].dist - 1LL * q[ptr].dep * mid, q[ptr].org)), ptr--;
        pair<ll, ll> matching = ((fir.second == q[i].org) ? sec : fir);
        if (matching.first < 1LL * q[i].dep * mid - q[i].dist)
            return true;
        update(make_pair(q[i].dist - 1LL * q[i].dep * mid, q[i].org));
    }
    return false;
}

bool check_negative(ll mid)
{
    fir = sec = make_pair(1LL << 60, 0);
    for (int i = start_pos - 1, ptr = start_pos; i >= 1; i--)
    {
        while (ptr <= tail && q[i].dist + q[ptr].dist < 0)
            update(make_pair(-q[ptr].dist + 1LL * q[ptr].dep * mid, q[ptr].org)), ptr++;
        pair<ll, ll> matching = ((fir.second == q[i].org) ? sec : fir);
        if (matching.first < q[i].dist - 1LL * q[i].dep * mid)
            return true;
        update(make_pair(-q[i].dist + 1LL * q[i].dep * mid, q[i].org));
    }
    return false;
}

void solve(int u, int capacity)
{
    tag[u] = true, q[tail = 1] = data{0, 0, 0};
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (!tag[edges[i].to])
            dfs(edges[i].to, u, 1, edges[i].weight, edges[i].to);
    sort(q + 1, q + 1 + tail), start_pos = 1;
    while (start_pos <= tail && q[start_pos].dist < 0)
        start_pos++;
    ll l = 1, r = ans - 1;
    while (l <= r)
    {
        ll mid = (l + r) >> 1;
        if (check_positive(mid) || check_negative(-mid))
            r = mid - 1;
        else
            l = mid + 1;
    }
    ans = min(ans, l);
    for (int i = head[u], sz; i != -1; i = edges[i].nxt)
        if (!tag[edges[i].to])
            sz = siz[edges[i].to], solve(getRoot(edges[i].to, sz), sz);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%lld", &n, &std_val);
    for (ll i = 1, u, v, w; i <= n - 1; i++)
    {
        scanf("%lld%lld%lld", &u, &v, &w);
        addpath(u, v, w - std_val), addpath(v, u, w - std_val), ans = min(ans, abs(w - std_val) + 1);
    }
    solve(getRoot(1, n), n), printf("%lld\n", ans - 1);
    return 0;
}