// J.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

typedef long long ll;
typedef pair<ll, int> pli;
typedef pair<int, int> pii;

int n, Q, tree[MAX_N << 1], anti[MAX_N << 1];
char str[MAX_N];
pli queries[MAX_N];
pii ansBox[MAX_N];

struct node
{
    int dep, link, ch[26], pos, lc, dfn;
} nodes[MAX_N << 1];

int ptot = 1, last_ptr = 1, bucket[MAX_N << 1], rnk[MAX_N << 1];
vector<int> G[MAX_N << 1];

void insert(int c, int idx)
{
    int pre = last_ptr, p = last_ptr = ++ptot;
    nodes[p].dep = nodes[pre].dep + 1, nodes[p].pos = idx;
    while (pre && nodes[pre].ch[c] == 0)
        nodes[pre].ch[c] = p, pre = nodes[pre].link;
    if (pre == 0)
        nodes[p].link = 1;
    else
    {
        int q = nodes[pre].ch[c];
        if (nodes[q].dep == nodes[pre].dep + 1)
            nodes[p].link = q;
        else
        {
            int clone = ++ptot;
            nodes[clone] = nodes[q], nodes[clone].dep = nodes[pre].dep + 1;
            nodes[p].link = nodes[q].link = clone;
            while (pre && nodes[pre].ch[c] == q)
                nodes[pre].ch[c] = clone, pre = nodes[pre].link;
        }
    }
}

void radixSort()
{
    for (int i = 1; i <= ptot; i++)
        bucket[nodes[i].dep]++;
    for (int i = 1; i <= ptot; i++)
        bucket[i] += bucket[i - 1];
    for (int i = 1; i <= ptot; i++)
        rnk[bucket[nodes[i].dep]--] = i;
    for (int i = 2; i <= ptot; i++)
        G[nodes[rnk[i]].link].push_back(rnk[i]);
}

int cnt;

void dfs1(int u)
{
    for (int v : G[u])
    {
        dfs1(v);
        nodes[u].pos = min(nodes[u].pos, nodes[v].pos);
        nodes[v].lc = str[nodes[v].pos + nodes[u].dep] - 'a';
    }
    sort(G[u].begin(), G[u].end(), [](const int &lhs, const int &rhs)
         { return nodes[lhs].lc < nodes[rhs].lc; });
}

void dfs2(int u)
{
    cnt++, nodes[u].dfn = cnt, anti[cnt] = u;
    for (int v : G[u])
        dfs2(v);
}

inline int lowbit(int x) { return x & -x; }

void update(int x, int d)
{
    for (; x <= ptot; x += lowbit(x))
        tree[x] += d;
}

int kth(int k)
{
    int ret = 0;
    for (int i = 22; i >= 0; i--)
    {
        ret += (1 << i);
        if (ret >= ptot || k <= tree[ret])
            ret -= (1 << i);
        else
            k -= tree[ret];
    }
    return ret + 1;
}

int main()
{
    scanf("%s", str + 1), n = strlen(str + 1), scanf("%d", &Q);
    for (int i = n; i >= 1; i--)
        insert(str[i] - 'a', i);
    for (int i = 1; i <= Q; i++)
        scanf("%lld", &queries[i].first), queries[i].second = i;
    sort(queries + 1, queries + 1 + Q), radixSort(), dfs1(1), dfs2(1);
    int qptr = 1, clen = 0, plen = 0;
    ll acc = 0;
    priority_queue<pii> pq;
    for (int v : G[1])
        pq.push(make_pair(-nodes[v].dep, v)), update(nodes[v].dfn, 1);
    while (!pq.empty())
    {
        clen = -pq.top().first;
        int cycle_len = clen - plen, cycle_width = pq.size();
        ll amount = 1LL * cycle_len * cycle_width;
        while (qptr <= Q && queries[qptr].first > acc && queries[qptr].first <= acc + amount)
        {
            ll order = queries[qptr].first - acc;
            ll nxt = (order - 1) % cycle_width, slen = (order - 1) / cycle_width;
            int id = anti[kth(nxt + 1)];
            ansBox[queries[qptr].second] = make_pair(nodes[id].pos, nodes[id].pos + clen + slen - 1);
            qptr++;
        }
        while (!pq.empty() && pq.top().first == -clen)
        {
            int u = pq.top().second;
            pq.pop();
            update(nodes[u].dfn, -1);
            for (int v : G[u])
                pq.push(make_pair(-nodes[v].dep, v)), update(nodes[v].dfn, 1);
        }
        plen = clen, acc += amount;
    }
    for (int i = 1; i <= Q; i++)
        if (ansBox[i].first == 0 && ansBox[i].second == 0)
            puts("-1 -1");
        else
            printf("%d %d\n", ansBox[i].first, ansBox[i].second);
    return 0;
}