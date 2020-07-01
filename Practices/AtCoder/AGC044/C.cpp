// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 631441;

int n, ptot = 1, ans[MAX_N], triple[MAX_N];
char str[MAX_N];

struct node
{
    int ch[3], val, pos;
    bool tag;
} nodes[MAX_N << 1];

void pushdown(int p)
{
    if (nodes[p].tag)
    {
        swap(nodes[p].ch[1], nodes[p].ch[2]), nodes[p].tag = false;
        for (int i = 0; i < 3; i++)
            if (nodes[p].ch[i])
                nodes[nodes[p].ch[i]].tag ^= 1;
    }
}

void update(int p)
{
    if (p == 0)
        return;
    pushdown(p);
    int tmp = nodes[p].ch[2];
    nodes[p].ch[2] = nodes[p].ch[1], nodes[p].ch[1] = nodes[p].ch[0], nodes[p].ch[0] = tmp;
    update(nodes[p].ch[0]);
}

void insert(int x, int ps)
{
    int p = 1;
    for (int i = 0; i < n; i++)
    {
        int b = x % 3;
        if (nodes[p].ch[b] == 0)
            nodes[p].ch[b] = ++ptot;
        p = nodes[p].ch[b], x /= 3;
    }
    nodes[p].pos = ps;
}

void collect(int u, int acc, int dep)
{
    if (dep == n)
        return (void)(ans[nodes[u].pos] = acc);
    pushdown(u);
    for (int i = 0; i < 3; i++)
        if (nodes[u].ch[i])
            collect(nodes[u].ch[i], acc + triple[dep] * i, dep + 1);
}

int main()
{
    scanf("%d%s", &n, str + 1);
    int upper = triple[0] = 1;
    for (int i = 1; i <= n; i++)
        upper *= 3, triple[i] = upper;
    for (int i = 0; i < upper; i++)
        insert(i, i);
    for (int i = 1; str[i]; i++)
        if (str[i] == 'S')
            nodes[1].tag ^= 1, pushdown(1);
        else
            update(1);
    collect(1, 0, 0);
    for (int i = 0; i < upper; i++)
        printf("%d ", ans[i]);
    puts("");
    return 0;
}