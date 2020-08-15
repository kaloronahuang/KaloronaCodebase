// CF587F.cpp
#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;
typedef long long ll;

const int MAX_N = 2e5 + 200;

int n, m, q, T, ch[MAX_N][26], pos[MAX_N], fa[MAX_N], link[MAX_N], len[MAX_N], ptot;
int sum[MAX_N], dtot, dfn[MAX_N], nodes[MAX_N];
ll ansBox[MAX_N];
char org[MAX_N];
vector<int> G[MAX_N];
vector<pii> ltag[MAX_N], rtag[MAX_N], lbtag[MAX_N], rbtag[MAX_N];

inline int lowbit(int x) { return x & (-x); }

void update(int x, int d)
{
    for (; x <= dtot; x += lowbit(x))
        nodes[x] += d;
}

int query(int x, int ret = 0)
{
    for (; x; x -= lowbit(x))
        ret += nodes[x];
    return ret;
}

void build()
{
    queue<int> q;
    for (int i = 0; i < 26; i++)
        if (ch[1][i])
            link[ch[1][i]] = 1, q.push(ch[1][i]);
        else
            ch[1][i] = 1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = 0; i < 26; i++)
            if (ch[u][i])
                link[ch[u][i]] = ch[link[u]][i], q.push(ch[u][i]);
            else
                ch[u][i] = ch[link[u]][i];
    }
}

void collect(int u)
{
    for (int v : G[u])
        collect(v), sum[u] += sum[v];
}

void dfs(int u)
{
    dfn[u] = ++dtot, sum[u] = 1;
    for (int v : G[u])
        dfs(v), sum[u] += sum[v];
}

int main()
{
    scanf("%d%d", &n, &q), ptot = 1;
    for (int i = 1; i <= n; i++)
    {
        scanf("%s", org + 1), len[i] = strlen(org + 1), m += len[i];
        int p = 1;
        for (int j = 1; j <= len[i]; j++)
        {
            if (ch[p][org[j] - 'a'] == 0)
                ch[p][org[j] - 'a'] = ++ptot, fa[ptot] = p;
            p = ch[p][org[j] - 'a'];
        }
        pos[i] = p;
    }
    build(), T = m / sqrt(q * log2(m));
    for (int i = 2; i <= ptot; i++)
        G[link[i]].push_back(i);
    for (int i = 1, l, r, k; i <= q; i++)
    {
        scanf("%d%d%d", &l, &r, &k);
        if (len[k] > T)
            ltag[k].push_back(make_pair(l, i)), rtag[k].push_back(make_pair(r, i));
        else
            lbtag[l].push_back(make_pair(k, i)), rbtag[r].push_back(make_pair(k, i));
    }
    for (int i = 1; i <= n; i++)
        if (len[i] > T)
        {
            int p = pos[i];
            while (p != 1)
                sum[p] = 1, p = fa[p];
            collect(1);
            sort(ltag[i].begin(), ltag[i].end()), sort(rtag[i].begin(), rtag[i].end());
            ll pre_sum = 0;
            int lptr = 0, rptr = 0, lsiz = ltag[i].size(), rsiz = rtag[i].size();
            for (int j = 1; j <= n; j++)
            {
                while (lptr < lsiz && ltag[i][lptr].first == j)
                    ansBox[ltag[i][lptr].second] -= pre_sum, lptr++;
                pre_sum += sum[pos[j]];
                while (rptr < rsiz && rtag[i][rptr].first == j)
                    ansBox[rtag[i][rptr].second] += pre_sum, rptr++;
            }
            for (int i = 2; i <= ptot; i++)
                sum[i] = 0;
        }
    dfs(1);
    for (int i = 1; i <= n; i++)
    {
        for (pii x : lbtag[i])
        {
            int p = pos[x.first];
            while (p != 1)
                ansBox[x.second] -= query(dfn[p]), p = fa[p];
        }
        update(dfn[pos[i]], 1), update(dfn[pos[i]] + sum[pos[i]], -1);
        for (pii x : rbtag[i])
        {
            int p = pos[x.first];
            while (p != 1)
                ansBox[x.second] += query(dfn[p]), p = fa[p];
        }
    }
    for (int i = 1; i <= q; i++)
        printf("%lld\n", ansBox[i]);
    return 0;
}