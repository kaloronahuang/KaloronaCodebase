// C.cpp
#include <bits/stdc++.h>
#pragma GCC optimize(2)

using namespace std;

const int MAX_N = 1e5 + 200;

int n, q, head[MAX_N], current, len, dist[MAX_N], fa[MAX_N], li[MAX_N], ri[MAX_N], ptot;

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
    return f * x;
}

struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void dfs(int u)
{
    li[u] = ++ptot;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        dist[edges[i].to] = dist[u] + edges[i].weight, dfs(edges[i].to);
    ri[u] = ptot;
}

namespace Subtask1
{

int seq[MAX_N], lft[MAX_N], rig[MAX_N], block_siz = 1000, block_tot, addtag[MAX_N], aff[MAX_N];
vector<int> ms[MAX_N];

void initialize()
{
    for (int i = 1; i <= n; i++)
        seq[li[i]] = dist[i];
    // block_siz = sqrt(n);
    for (int i = 1; i <= n; i += block_siz)
        lft[++block_tot] = i, rig[block_tot] = min(n, i + block_siz - 1);
    for (int b = 1; b <= block_tot; b++)
    {
        for (int i = lft[b]; i <= rig[b]; i++)
            ms[b].push_back(seq[i]), aff[i] = b;
        sort(ms[b].begin(), ms[b].end());
    }
}

void raw_update(int l, int r, int val)
{
    int b = aff[l];
    ms[b].clear();
    for (int i = l; i <= r; i++)
        seq[i] += val;
    for (int i = lft[b]; i <= rig[b]; i++)
        ms[b].push_back(seq[i]);
    sort(ms[b].begin(), ms[b].end());
}

void update(int l, int r, int val)
{
    int lb = aff[l], rb = aff[r];
    if (lb == rb)
        raw_update(l, r, val);
    else
    {
        raw_update(l, rig[aff[l]], val), raw_update(lft[aff[r]], r, val);
        for (int b = lb + 1; b <= rb - 1; b++)
            addtag[b] += val;
    }
}

int check(int mid, int l, int r)
{
    int lb = aff[l], rb = aff[r], cnt = 0;
    if (lb == rb)
        for (int i = l; i <= r; i++)
        {
            int real_val = seq[i] + addtag[aff[i]];
            if (real_val <= mid)
                cnt++;
        }
    else
    {
        for (int i = l; i <= rig[aff[l]]; i++)
        {
            int real_val = seq[i] + addtag[aff[i]];
            if (real_val <= mid)
                cnt++;
        }
        for (int i = lft[aff[r]]; i <= r; i++)
        {
            int real_val = seq[i] + addtag[aff[i]];
            if (real_val <= mid)
                cnt++;
        }
        for (int b = aff[l] + 1; b <= aff[r] - 1; b++)
            cnt += upper_bound(ms[b].begin(), ms[b].end(), mid - addtag[b]) - ms[b].begin();
    }
    return cnt;
}

void solve()
{
    initialize();
    while (q--)
    {
        int opt = read(), x = read(), k = read();
        if (opt == 1)
            if (ri[x] - li[x] + 1 < k)
                puts("-1");
            else
            {
                int l = 0, r = n * len * 2, res = 0;
                while (l <= r)
                {
                    int mid = (l + r) >> 1;
                    if (check(mid, li[x], ri[x]) >= k)
                        r = mid - 1, res = mid;
                    else
                        l = mid + 1;
                }
                printf("%d\n", res);
            }
        else
            // the interval gonna be modified;
            // increase by k;
            update(li[x], ri[x], k);
    }
}

} // namespace Subtask1

int main()
{
    memset(head, -1, sizeof(head));
    n = read(), q = read(), len = read();
    for (int i = 2, upweight; i <= n; i++)
        fa[i] = read(), upweight = read(), addpath(fa[i], i, upweight);
    dfs(1);
    Subtask1::solve();
    return 0;
}