// P2279.cpp
#include <iostream>
#include <stack>
#include <queue>
using namespace std;

const int maxn = 4040;

struct edge
{
    int to, next;
} edges[maxn];
int head[maxn];
int F[maxn];
stack<int> st;
bool vis[maxn];
int current = 0;
int n;

void addpath(int src, int dst)
{
    edges[current].to = dst;
    edges[current].next = head[src];
    head[src] = current++;
}

void BFS()
{
    queue<int> q;
    q.push(1);
    st.push(1);
    while (!q.empty())
    {
        int curt = q.front();
        q.pop();
        for (int i = head[curt]; i != -1; i = edges[i].next)
            if (edges[i].to != F[curt])
                st.push(edges[i].to), q.push(edges[i].to);
    }
}

void DFS(int p, int dep)
{
    if (dep > 2)
        return;
    vis[p] = true;
    for (int i = head[p]; i != -1; i = edges[i].next)
        DFS(edges[i].to, dep + 1);
}

int main()
{
    cin >> n;
    fill(head, head + maxn, -1);
    fill(vis, vis + maxn, false);
    int num = -1;
    for (int i = 2; i <= n; i++)
    {
        cin >> num;
        F[i] = num;
        addpath(num, i), addpath(i, num);
    }
    // going to solve;
    BFS();
    int ans = 0;
    while (!st.empty())
    {
        int curt = st.top();
        st.pop();
        if (!vis[curt] && ++ans)
            DFS(F[F[curt]], 0);
    }
    cout << ans;
    return 0;
}