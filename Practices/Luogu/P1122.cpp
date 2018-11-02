// P1122.cpp
#include <iostream>
#include <algorithm>

using namespace std;
// the tree;
const int maxn = 160010;
int n;
int dis[maxn];
int to[maxn];
int next[maxn];
int point[maxn];
int current = 0;
int F[maxn];
int ans = 0;

void add_edge(int src, int dst)
{
    next[current] = point[src];
    to[current] = dst;
    point[src] = current;
    current++;
}
// core code: search subtrees and add them up to F[curt],
// in the meanwhile, get the ans;
void DFS(int curt, int fat)
{
    F[curt] = dis[curt];
    for (int i = point[curt]; i != -1; i = next[i])
    {
        int dst = to[i];
        if (dst == fat)
            continue;
        DFS(dst, curt);
        F[curt] += max(0, F[dst]);
    }
    ans = max(ans, F[curt]);
}
// initialize;
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> dis[i];
    fill(point, point + n + 1, -1);
    fill(next, next + n + 1, -1);
    fill(F, F + n + 1, 0);
    int a, b;
    for (int i = 0; i < n - 1; i++)
    {
        cin >> a >> b;
        add_edge(a, b), add_edge(b, a);
    }
    DFS(1, 0);
    cout << ans;
    return 0;
}