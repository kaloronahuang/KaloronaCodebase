// BZ3611.cpp
#include <bits/stdc++.h>
#pragma comment(linker, "/STACK:102400000,102400000")

using namespace std;

const int MAX_N = 4e6 + 200;

typedef pair<int, int> pii;
typedef long long ll;

int n, q, head[MAX_N], current, dep[MAX_N], stot, st[20][MAX_N], log2_[MAX_N], pos[MAX_N];
int ktot, kseq[MAX_N], stk[MAX_N << 2], dtot, siz[MAX_N], mpos;
bool vis[MAX_N];
ll ans, ans1, ans2;
vector<int> G[MAX_N];
set<int> pool;

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

inline char nc()
{
    static char buf[1000000], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1000000, stdin), p1 == p2) ? EOF : *p1++;
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

int dcnt;

void dfs(int u, int fa)
{
    // st[0][++stot] = u, pos[u] = stot, dep[u] = dep[fa] + 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dfs(edges[i].to, u); //, st[0][++stot] = u;
}

int gmin(int x, int y) { return dep[x] < dep[y] ? x : y; }

int getLCA(int x, int y)
{
    if (pos[x] > pos[y])
        swap(x, y);
    int d = log2_[pos[y] - pos[x] + 1];
    return gmin(st[d][pos[x]], st[d][pos[y] - (1 << d) + 1]);
}

void build_virtual_tree()
{
    for (int x : pool)
        G[x].clear(), siz[x] = 0;
    ktot = read(), pool.clear(), G[1].clear();
    for (int i = 1; i <= ktot; i++)
        kseq[i] = read(), vis[kseq[i]] = true;
    sort(kseq + 1, kseq + 1 + ktot, [](const int &rhs1, const int &rhs2) { return pos[rhs1] < pos[rhs2]; });
    int tail = 0;
    stk[++tail] = 1, pool.insert(1);
    for (int i = 1; i <= ktot; i++)
        if (kseq[i] != 1)
        {
            int x = kseq[i], d = getLCA(x, stk[tail]);
            if (d != stk[tail])
            {
                while (pos[stk[tail - 1]] > pos[d])
                    G[stk[tail - 1]].push_back(stk[tail]), tail--;
                if (pos[stk[tail - 1]] < pos[d])
                    G[d].clear(), G[d].push_back(stk[tail]), stk[tail] = d, pool.insert(d);
                else
                    G[d].push_back(stk[tail]), tail--, pool.insert(d);
            }
            G[stk[++tail] = x].clear(), pool.insert(d), mpos = max(mpos, tail);
        }
    for (int i = 1; i < tail; i++)
        G[stk[i]].push_back(stk[i + 1]);
}

pair<ll, ll> vdfs(int u)
{
    siz[u] = (vis[u] == true);
    ll longest = 0, shortest = (vis[u] ? 0 : 0x3f3f3f3f3f3f3f3f);
    for (int v : G[u])
    {
        pair<ll, ll> res = vdfs(v);
        ll seg = res.first, sseg = res.second, len = dep[v] - dep[u];
        ans += 1LL * siz[v] * (ktot - siz[v]) * len;
        if (siz[u])
        {
            ans1 = min(ans1, shortest + sseg + len);
            ans2 = max(ans2, longest + seg + len);
        }
        shortest = min(shortest, sseg + len);
        longest = max(longest, seg + len);
        siz[u] += siz[v];
    }
    vis[u] = false;
    return make_pair(longest, vis[u] ? 0 : shortest);
}

int main()
{

    freopen("5.in", "r", stdin);
    freopen("test.out", "w", stdout);

    memset(head, -1, sizeof(head)), n = read();
    for (int i = 1, u, v; i <= n - 1; i++)
        u = read(), v = read(), addpath(u, v), addpath(v, u);
    dfs(1, 0), q = read();
    for (int i = 2; i <= stot; i++)
        log2_[i] = log2_[i >> 1] + 1;
    for (int i = 1; i < 20; i++)
        for (int j = 1; j + (1 << i) - 1 <= stot; j++)
            st[i][j] = gmin(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
    while (q--)
    {
        build_virtual_tree(), ans = 0, ans1 = 0x3f3f3f3f3f3f3f3f, ans2 = 0;
        vdfs(1), printf("%lld %lld %lld\n", ans, ans1, ans2);
        // fflush(stdout);
        // cerr << mpos << endl;
    }
    return 0;
}