// A.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAX_N = 5e3 + 200, MAX_E = 2e5 + 200;
int n, m, head[MAX_N], tmpx, tmpy, tmpz, current, q;
ll dist[MAX_N];
bool vis[MAX_N];
char opt[10];
struct edge
{
    int to, nxt, weight;
} edges[MAX_E << 1];
void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].weight = weight;
    edges[current].nxt = head[src], head[src] = current++;
}
void djisktra(int src)
{
    memset(vis, 0, sizeof(vis)), memset(dist, 0x3f, sizeof(dist));
    queue<int> pq;
    dist[src] = 0, pq.push(src);
    while (!pq.empty())
    {
        int curt = pq.front();
        pq.pop();
        if (vis[curt])
            continue;
        vis[curt] = true;
        for (int i = head[curt]; i != -1; i = edges[i].nxt)
            if (dist[edges[i].to] > max((ll)edges[i].weight, dist[curt]))
                dist[edges[i].to] = max((ll)edges[i].weight, dist[curt]), pq.push(edges[i].to);
    }
}
bool nim(int a, int b)
{
    bool strangeSitu = false;
    int arr[3];
    arr[1] = a, arr[2] = b;
    for (int i = 1; i <= 2 && !strangeSitu; i++)
    {
        int tot = 0;
        for (int j = 1; j <= 2; j++)
            if (j != i)
                if (j != 1)
                    tot ^= arr[j];
                else
                    tot = arr[j];
        if (tot == arr[i])
            strangeSitu = true;
    }
    return !strangeSitu;
}
int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
        scanf("%d%d%d", &tmpx, &tmpy, &tmpz), addpath(tmpx, tmpy, tmpz), addpath(tmpy, tmpx, tmpz);
    scanf("%d", &q);
    while (q--)
    {
        scanf("%s", opt + 1);
        if (opt[1] == 'g')
        {
            int m1, m2, b1, b2, dist1, dist2;
            scanf("%d%d%d%d", &m1, &m2, &b1, &b2);
            djisktra(m1), dist1 = dist[m2];
            djisktra(b1), dist2 = dist[b2];
            if (nim(dist1, dist2))
                printf("madoka\n");
            else
                printf("Baozika\n");
        }
        else
            scanf("%d%d%d", &tmpx, &tmpy, &tmpz), addpath(tmpx, tmpy, tmpz), addpath(tmpy, tmpx, tmpz);
    }
    return 0;
}