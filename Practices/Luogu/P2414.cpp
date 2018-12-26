// P2414.cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
#define lowbit(num) (num & -num)
using namespace std;
const int MX_N = 200200;
int head[MX_N], current = 0;
struct egde
{
    int to, nxt;
} edges[MX_N];
char buff[MX_N];
int T, anses[MX_N], root, nds[MX_N], tree[MX_N], tim, n, ql[MX_N], qr[MX_N], tot;
struct node
{
    int nxt[26], fail, fa, pre[26], id, dfn, low;
} nodes[MX_N];
struct queryInfo
{
    int x, y, ans, id;
    bool operator<(const queryInfo &q) const { return y < q.y; }
} qi[MX_N];
inline int read()
{
    int x = 0, t = 1;
    char ch = getchar();
    while ((ch < '0' || ch > '9') && ch != '-')
        ch = getchar();
    if (ch == '-')
        t = -1, ch = getchar();
    while (ch <= '9' && ch >= '0')
        x = x * 10 + ch - 48, ch = getchar();
    return x * t;
}
void addpath(int src, int dst) { edges[current].to = dst, edges[current].nxt = head[src], head[src] = current++; }
void update(int x, int c)
{
    while (x <= tim)
        tree[x] += c, x += lowbit(x);
}
int getsum(int x)
{
    int ret = 0;
    while (x > 0)
        ret += tree[x], x -= lowbit(x);
    return ret;
}
void insert(string str, int id)
{
    int p = root;
    for (int i = 0; i < str.length(); i++)
    {
        int curt = str[i] - 'a', fa = p;
        if (nodes[p].nxt[curt] == 0)
            nodes[p].nxt[curt] = ++tot;
        p = nodes[p].nxt[curt];
        nodes[p].fa = fa;
    }
    nodes[p].id = id, nds[id] = p;
}
void bfs()
{
    queue<int> q;
    for (int i = 0; i < 26; i++)
        if (nodes[root].nxt[i] != 0)
            q.push(nodes[root].nxt[i]);
    while (!q.empty())
    {
        int curt = q.front();
        q.pop();
        for (int i = 0; i < 26; i++)
            if (nodes[curt].nxt[i] != 0)
                nodes[nodes[curt].nxt[i]].fail = nodes[nodes[curt].fail].nxt[i],
                q.push(nodes[curt].nxt[i]);
            else
                nodes[curt].nxt[i] = nodes[nodes[curt].fail].nxt[i];
    }
}
void dfs(int u)
{
    nodes[u].dfn = ++tim;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        dfs(edges[i].to);
    nodes[u].low = tim;
}
void dfsans(int u)
{
    update(nodes[u].dfn, 1);
    if (nodes[u].id != 0)
        for (int i = ql[nodes[u].id]; i <= qr[nodes[u].id]; i++)
            qi[i].ans = getsum(nodes[nds[qi[i].x]].low) - getsum(nodes[nds[qi[i].x]].dfn - 1);
    for (int i = 0; i < 26; i++)
        if (nodes[u].pre[i] != 0)
            dfsans(nodes[u].nxt[i]);
    update(nodes[u].dfn, -1);
}
int main()
{
    memset(head, -1, sizeof(head));
    root = 0;
    scanf("%s", buff + 1);
    int now = root;
    for (int i = 1, l = strlen(buff + 1); i <= l; ++i)
    {
        if (buff[i] >= 'a' && buff[i] <= 'z')
        {
            if (!nodes[now].nxt[buff[i] - 'a'])
                nodes[now].nxt[buff[i] - 'a'] = ++tot, nodes[tot].fa = now;
            now = nodes[now].nxt[buff[i] - 'a'];
        }
        if (buff[i] == 'B')
            now = nodes[now].fa;
        if (buff[i] == 'P')
        {
            nds[++n] = now;
            nodes[now].id = n;
        }
    }
    for (int i = 0; i <= tot; i++)
        for (int j = 0; j < 26; j++)
            nodes[i].pre[j] = nodes[i].nxt[j];
    bfs();
    for (int i = 1; i <= tot; i++)
        addpath(nodes[i].fail, i);
    dfs(root);
    T = read();
    for (int i = 1; i <= T; i++)
        qi[i].x = read(), qi[i].y = read(), qi[i].id = i;
    sort(qi + 1, qi + 1 + T);
    for (int i = 1, pos = 1; i <= T; i = pos)
    {
        ql[qi[i].y] = i;
        while (qi[i].y == qi[pos].y)
            pos++;
        qr[qi[i].y] = pos - 1;
    }
    dfsans(root);
    for (int i = 1; i <= T; i++)
        anses[qi[i].id] = qi[i].ans;
    for (int i = 1; i <= T; i++)
        printf("%d\n", anses[i]);
    return 0;
}