// LOJ2313.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int n, q, T, ptot = 1, last_ptr = 1, pos[MAX_N], lcp[MAX_N], max_pos[MAX_N];
long long ansBox[MAX_N], qu[MAX_N], h[MAX_N];
char str[MAX_N];

struct query
{
    int l, r, id;
    bool operator<(const query &rhs) const { return r < rhs.r; }
} queries[MAX_N];

struct node
{
    int ch[2], dep, link;
} nodes[MAX_N << 1];

void insert(int c, int id)
{
    int pre = last_ptr, p = last_ptr = ++ptot;
    nodes[p].dep = nodes[pre].dep + 1, pos[id] = p;
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

void update(int position)
{
    int p = pos[position];
    while (p)
    {
        lcp[nodes[p].dep] = max(lcp[nodes[p].dep], max_pos[p]);
        if (lcp[nodes[p].dep])
            T = max(T, nodes[p].dep);
        max_pos[p] = max(max_pos[p], position), p = nodes[p].link;
    }
}

void calc(int position)
{
    int pt = queries[position].r - 1, top = 0;
    long long ret = 0;
    for (int i = 1; i <= T; i++)
        if (lcp[i])
        {
            while (lcp[i] >= qu[top] && top)
                top--;
            qu[++top] = lcp[i], h[top] = i;
        }
    qu[top + 1] = 0;
    for (int i = 2; i <= top + 1; i++)
    {
        if (qu[i] < queries[position].l)
        {
            ret += 1LL * (qu[i - 1] - queries[position].l + 1) * h[i - 1];
            break;
        }
        ret += (qu[i - 1] - qu[i]) * h[i - 1];
    }
    ansBox[queries[position].id] = ret;
}

int main()
{
    scanf("%d%d%s", &n, &q, str + 1);
    for (int i = 1; i <= q; i++)
        scanf("%d%d", &queries[i].l, &queries[i].r), queries[i].id = i;
    sort(queries + 1, queries + 1 + q);
    for (int i = n; i >= 1; i--)
        insert(str[i] - '0', i);
    update(1);
    int ptr = 1;
    for (int i = 2; i <= n; i++)
    {
        update(i);
        while (queries[ptr].r == i)
            calc(ptr++);
    }
    for (int i = 1; i <= q; i++)
        printf("%lld\n", ansBox[i]);
    return 0;
}