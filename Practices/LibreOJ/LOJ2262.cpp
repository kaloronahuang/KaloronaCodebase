// LOJ2262.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 1e5 + 200;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int n, L, head[MAX_N], current, root, fa[MAX_N], diameterSeq[MAX_N], dtot, idx1[MAX_N], idx2[MAX_N];
ll dist[MAX_N], branchRatio[MAX_N];
bool tag[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].weight = weight;
    edges[current].nxt = head[src], head[src] = current++;
}

void preprocess(int u)
{
    if (dist[u] > dist[root])
        root = u;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa[u])
        {
            dist[edges[i].to] = dist[u] + edges[i].weight;
            fa[edges[i].to] = u, preprocess(edges[i].to);
        }
}

ll dfsBranch(int u, int fat, ll prefix)
{
    ll ret = prefix;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fat && tag[edges[i].to] == false)
            ret = max(ret, dfsBranch(edges[i].to, u, prefix + edges[i].weight));
    return ret;
}

bool check(ll mid)
{
    ll al = -INF, bl = -INF, amax = -INF;
    ll ar = INF, br = INF, bmin = INF;
    for (int i = 1, ptr = 1; i <= dtot; i++)
    {
        while (ptr <= dtot && dist[idx1[i]] + branchRatio[idx1[i]] - dist[idx2[ptr]] + branchRatio[idx2[ptr]] > mid)
        {
            amax = max(amax, dist[idx2[ptr]] + branchRatio[idx2[ptr]]);
            bmin = min(bmin, dist[idx2[ptr]] - branchRatio[idx2[ptr]]);
            ptr++;
        }
        if (ptr > 1)
        {
            al = max(al, dist[idx1[i]] + branchRatio[idx1[i]] + amax);
            ar = min(ar, dist[idx1[i]] - branchRatio[idx1[i]] + bmin);
            bl = max(bl, dist[idx1[i]] + branchRatio[idx1[i]] - bmin);
            br = min(br, dist[idx1[i]] - branchRatio[idx1[i]] - amax);
        }
    }
    al += L - mid, ar += mid - L, bl += L - mid, br += mid - L;
    if (al > ar || bl > br)
        return false;
    for (int i = 1, j = 1, k = 1, x = dtot, y = dtot; i <= dtot; i++)
    {
        while (j <= dtot && dist[diameterSeq[i]] - dist[diameterSeq[j]] >= bl)
            j++;
        while (k <= dtot && dist[diameterSeq[i]] - dist[diameterSeq[k]] > br)
            k++;
        while (x > 0 && dist[diameterSeq[i]] + dist[diameterSeq[x]] >= al)
            x--;
        while (y > 0 && dist[diameterSeq[i]] + dist[diameterSeq[y]] > ar)
            y--;
        if (max(k, x + 1) <= min(j - 1, y))
            return true;
    }
    return false;
}

int main()
{
    while (scanf("%d%d", &n, &L) && n && L)
    {
        memset(head, -1, sizeof(head)), current = 0, memset(tag, false, sizeof(tag));
        memset(dist, 0, sizeof(dist)), memset(branchRatio, 0, sizeof(branchRatio));
        memset(fa, 0, sizeof(fa)), memset(idx1, 0, sizeof(idx1)), memset(idx2, 0, sizeof(idx2));
        memset(diameterSeq, 0, sizeof(diameterSeq)), dtot = 0;
        for (int i = 1, u, v, w; i <= n - 1; i++)
            scanf("%d%d%d", &u, &v, &w), addpath(u, v, w), addpath(v, u, w);
        int A, B;
        root = 1, preprocess(1), A = root;
        fa[root] = dist[root] = 0, preprocess(root), B = root;
        for (int pt = B; pt; pt = fa[pt])
            tag[pt] = true, diameterSeq[++dtot] = pt;
        reverse(diameterSeq + 1, diameterSeq + dtot + 1);

        for (int i = 1; i <= dtot; i++)
        {
            int u = diameterSeq[i];
            branchRatio[u] = dfsBranch(u, 0, 0);
            idx1[i] = idx2[i] = u;
        }
        sort(idx1 + 1, idx1 + 1 + dtot, [](const int &a, const int &b) { return dist[a] + branchRatio[a] < dist[b] + branchRatio[b]; });
        sort(idx2 + 1, idx2 + 1 + dtot, [](const int &a, const int &b) { return dist[a] - branchRatio[a] < dist[b] - branchRatio[b]; });
        ll l = 0, r = dist[diameterSeq[dtot]], res = r;
        while (l <= r)
        {
            ll mid = (l + r) >> 1;
            if (check(mid))
                res = mid, r = mid - 1;
            else
                l = mid + 1;
        }
        printf("%lld\n", res);
    }
    return 0;
}