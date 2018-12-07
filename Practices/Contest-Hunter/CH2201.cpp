// CH2201.cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#define reg register
using namespace std;
const int maxn = 20;
int N, W, weights[maxn], ans = 1e9, cab[maxn], tot = 0;
bool vis[maxn];
void dfs(int u)
{
    if (tot > ans)
        return;
    if (u == N + 1)
    {
        ans = min(ans, tot);
        return;
    }
    for (reg int i = 0; i < tot; i++)
        if (cab[i] + weights[u] <= W)
        {
            cab[i] += weights[u];
            dfs(u + 1);
            cab[i] -= weights[u];
        }
    cab[tot++] = weights[u];
    dfs(u + 1);
    tot--;
}
int main()
{
    scanf("%d%d", &N, &W);
    for (reg int i = 1; i <= N; i++)
        scanf("%d", &weights[i]);
    sort(weights + 1, weights + N + 1), reverse(weights + 1, weights + N + 1);
    ans = N;
    vis[1] = true;
    dfs(1);
    printf("%d", ans);
    return 0;
}