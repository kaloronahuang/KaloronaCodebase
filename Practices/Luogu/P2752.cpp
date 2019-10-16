// P2752.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 110;

int head[MAX_N], current, n, m, tmp;
vector<int> ans1, ans2;
bool vis[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &tmp);
    while (tmp != -1)
    {
        while (tmp != -2 && tmp != -1)
            addpath(n, tmp), scanf("%d", &tmp);
        scanf("%d", &tmp), n++;
    }
    n--;
    for (int pt = 1; pt <= n - 1; pt++)
    {
        memset(vis, false, sizeof(vis)), vis[0] = true;
        queue<int> q;
        q.push(0);
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (int i = head[u]; i != -1; i = edges[i].nxt)
                if (edges[i].to != pt && vis[edges[i].to] == false)
                    q.push(edges[i].to), vis[edges[i].to] = true;
        }
        if (vis[n] == false)
        {
            ans1.push_back(pt);
            bool flag = true;
            for (int u = 0; u <= n; u++)
                if (!vis[u])
                    for (int i = head[u]; i != -1; i = edges[i].nxt)
                        if (vis[edges[i].to] == true)
                            flag = false;
            if (flag)
                ans2.push_back(pt);
        }
    }
    printf("%d ", ans1.size());
    for (int pt : ans1)
        printf("%d ", pt);
    printf("\n%d ", ans2.size());
    for (int pt : ans2)
        printf("%d ", pt);
    return 0;
}