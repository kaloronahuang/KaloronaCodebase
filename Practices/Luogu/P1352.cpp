// P1352.cpp
#include <iostream>

using namespace std;
// Data Structure;
const int maxn = 6100;
int n;
int R[maxn];
// Graph stuff;
// Notice: the edge space should be doubled;
struct edge
{
    int to, next;
} edges[maxn << 1];
int head[maxn];
int current = 0;
int F[maxn][2];
int deg[maxn];
// DFS func;
void DFS(int curt)
{
    // Initalize the DP Table;
    F[curt][1] = R[curt];
    // Find the subnodes;
    for (int i = head[curt]; i != -1; i = edges[i].next)
    {
        // Call the subtree to be ready;
        DFS(edges[i].to);
        // Deciding;
        F[curt][1] += F[edges[i].to][0];
        F[curt][0] += max(F[edges[i].to][0], F[edges[i].to][1]);
    }
}

void add_path(int src, int dst)
{
    edges[current].to = dst;
    edges[current].next = head[src];
    head[src] = current++;
}

int main()
{
    // Initialize;
    cin >> n;
    fill(head, head + maxn, -1);
    for (int i = 1; i <= n; i++)
        cin >> R[i];
    int a, b;
    for (int i = 1; i <= n - 1; i++)
    {
        cin >> a >> b, add_path(b, a);
        deg[a]++;
    }
    cin >> a >> b;
    // Find the root node by the degrees saved before;
    int root = 0;
    for (int i = 1; i <= n; i++)
        if (deg[i] == 0)
        {
            root = i;
            break;
        }
    // Start to dp;
    DFS(root);
    // Output;
    cout << max(F[root][0], F[root][1]);
    return 0;
}