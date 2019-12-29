// P1117.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 6e4 + 200;

int pre[MAX_N], suf[MAX_N], T, n;
char str[MAX_N];

struct node
{
    int ch[26], link, dep;
};

struct SAM
{
    node nodes[MAX_N];
    int last_ptr = 1, ptot = 1, fa[20][MAX_N], pos[MAX_N];
    int dep[MAX_N], head[MAX_N], current;

    struct edge
    {
        int to, nxt;
    } edges[MAX_N << 1];

    void addpath(int src, int dst)
    {
        edges[current].to = dst, edges[current].nxt = head[src];
        head[src] = current++;
    }

    void insert(int c, int idx)
    {
        int pre = last_ptr, p = last_ptr = ++ptot;
        nodes[p].dep = nodes[pre].dep + 1, pos[idx] = last_ptr;
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

    void dfs(int u)
    {
        dep[u] = dep[fa[0][u]] + 1;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            fa[0][edges[i].to] = u, dfs(edges[i].to);
    }

    void init_tree()
    {
        memset(head, -1, sizeof(head)), current = 0;
        for (int i = 1; i <= ptot; i++)
            if (nodes[i].link != 0)
                addpath(nodes[i].link, i);
        dfs(1);
        for (int i = 1; i <= 19; i++)
            for (int j = 1; j <= ptot; j++)
                fa[i][j] = fa[i - 1][fa[i - 1][j]];
    }

    int query(int x, int y)
    {
        x = pos[x], y = pos[y];
        if (dep[x] < dep[y])
            swap(x, y);
        for (int i = 19; i >= 0; i--)
            if (dep[fa[i][x]] >= dep[y])
                x = fa[i][x];
        if (x == y)
            return nodes[x].dep;
        for (int i = 19; i >= 0; i--)
            if (fa[i][x] != fa[i][y])
                x = fa[i][x], y = fa[i][y];
        return nodes[fa[0][x]].dep;
    }

} SAM_OPT, SAM_REV, zero;

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        memset(pre, 0, sizeof(pre)), memset(suf, 0, sizeof(suf));
        scanf("%s", str + 1), n = strlen(str + 1);
        SAM_OPT = zero, SAM_REV = zero;
        for (int i = 1; i <= n; i++)
            SAM_OPT.insert(str[i] - 'a', i);
        for (int i = n; i >= 1; i--)
            SAM_REV.insert(str[i] - 'a', i);
        SAM_OPT.init_tree(), SAM_REV.init_tree();
        for (int len = 1; len <= (n >> 1); len++)
            for (int i = len; i <= (n - len + 1); i += len)
            {
                int j = i + len, x = 0, y = 0;
                if (j <= n)
                    x = min(SAM_REV.query(i, j), len);
                if (i > 1)
                    y = min(SAM_OPT.query(i - 1, j - 1), len - 1);
                if (x + y < len)
                    continue;
                pre[j + x]--, pre[j + x - 1 - (x + y - len)]++;
                suf[i - y]++, suf[i - y + 1 + (x + y - len)]--;
            }
        for (int i = 1; i <= n; i++)
            pre[i] += pre[i - 1], suf[i] += suf[i - 1];
        long long answer = 0;
        for (int i = 2; i <= n; i++)
            answer += 1LL * pre[i - 1] * suf[i];
        printf("%lld\n", answer);
    }
    return 0;
}