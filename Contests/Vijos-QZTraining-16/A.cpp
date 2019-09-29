// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 42, MAX_H = 5e6 + 200, MAX_E = 1e5 + 200;

int n, m, seq[MAX_N];

struct hashTable
{
    int head[MAX_E], current;

    void clear() { memset(head, -1, sizeof(head)), current = 0; }

    struct edge
    {
        int key, nxt;
    } edges[MAX_H];

    bool query(int x)
    {
        int id = (x + MAX_E) % MAX_E;
        for (int i = head[id]; i != -1; i = edges[i].nxt)
            if (edges[i].key == x)
                return true;
        return false;
    }

    void insert(int x)
    {
        if (query(x))
            return;
        int id = (x + MAX_E) % MAX_E;
        edges[current].key = x, edges[current].nxt = head[id];
        head[id] = current++;
    }
} mp;

void dfs1(int pos, int cnt)
{
    if (cnt > m)
        return;
    if (pos == (n >> 1) + 1)
    {
        mp.insert(cnt);
        return;
    }
    dfs1(pos + 1, cnt);
    dfs1(pos + 1, cnt + seq[pos]);
}

bool dfs2(int pos, int cnt)
{
    if (cnt > m)
        return false;
    if (pos == n + 1)
        return mp.query(m - cnt);
    if (dfs2(pos + 1, cnt + seq[pos]) || dfs2(pos + 1, cnt))
        return true;
    return false;
}

int main()
{
    while (scanf("%d%d", &n, &m) && n != 0 && m != 0)
    {
        mp.clear();
        for (int i = 1; i <= n; i++)
            scanf("%d", &seq[i]);
        dfs1(1, 0);
        if (dfs2((n >> 1) + 1, 0))
            puts("YES");
        else
            puts("NO");
    }
    return 0;
}