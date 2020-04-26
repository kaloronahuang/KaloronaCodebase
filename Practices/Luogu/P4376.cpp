// P4376.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, m, head[MAX_N], current, mi[MAX_N], deg[MAX_N];
vector<int> seqs[MAX_N], ansBox;

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

bool check(int mid)
{
    memset(head, -1, sizeof(head)), current = 0, ansBox.clear();
    memset(deg, 0, sizeof(deg));
    for (int i = 1; i <= mid; i++)
        for (int j = 0; j < mi[i] - 1; j++)
            addpath(seqs[i][j], seqs[i][j + 1]), deg[seqs[i][j + 1]]++;
    priority_queue<int> pq;
    for (int i = 1; i <= n; i++)
        if (deg[i] == 0)
            pq.push(-i);
    while (!pq.empty())
    {
        int u = -pq.top();
        pq.pop(), ansBox.push_back(u);
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (--deg[edges[i].to] == 0)
                pq.push(-edges[i].to);
    }
    for (int i = 1; i <= n; i++)
        if (deg[i] != 0)
            return false;
    return true;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d", &mi[i]);
        for (int j = 1, val; j <= mi[i]; j++)
            scanf("%d", &val), seqs[i].push_back(val);
    }
    int l = 0, r = m, res = 0;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (check(mid))
            l = mid + 1, res = mid;
        else
            r = mid - 1;
    }
    check(res);
    for (int i = 1; i <= n; i++)
        printf("%d ", ansBox[i - 1]);
    return 0;
}