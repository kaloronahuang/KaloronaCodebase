// A.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 100;
int head[MAX_N], n, current, matching[MAX_N], dfn[MAX_N], arr[MAX_N];
bool isPrime[2020];
struct edge
{
    int to, nxt;
} edges[(MAX_N * (MAX_N - 1)) >> 1];
void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}
bool dfs(int u, int org)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
    {
        int to = edges[i].to;
        if (dfn[to] != org)
        {
            dfn[to] = org;
            if ((!matching[to]) || dfs(matching[to], org))
            {
                matching[to] = u;
                return true;
            }
        }
    }
    return false;
}
int main()
{
    freopen("prime.in", "r", stdin);
    freopen("prime.out", "w", stdout);
    memset(head, -1, sizeof(head)), memset(isPrime, true, sizeof(isPrime));
    int ans = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &arr[i]);
    for (int i = 2; i < 2020; i++)
        if (isPrime[i])
            for (int j = 2; i * j < 2020; j++)
                isPrime[j * i] = false;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (isPrime[arr[i] + arr[j]])
                addpath(i, j);
    for (int i = 1; i <= n; i++)
        if (dfs(i, i))
            ans++;
    printf("%d", ans / 2);
    return 0;
}