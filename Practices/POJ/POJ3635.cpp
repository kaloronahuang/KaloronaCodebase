// POJ3635.cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 2000;
int head[maxn], cost[maxn], current = 0, N, M, Q;
struct edge
{
    int to, weight, next;
} edges[20200];
void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].next = head[src];
    edges[current].weight = weight, head[src] = current++;
}
int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &N, &M);
    for (int i = 0; i < N; i++)
        scanf("%d", &cost[i]);
    for (int i = 0; i < M; i++)
    {
        int src, dst, w;
        scanf("%d%d%d", &src, &dst, &w);
        addpath(src, dst, w), addpath(dst, src, w);
    }
    scanf("%d", &Q);
    while (Q--)
    {
    }
    return 0;
}