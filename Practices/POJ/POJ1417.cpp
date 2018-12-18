// POJ1417.cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
const int maxn = 400, maxm = 2010;
int n, p1, p2, fa[maxm], tot, cnt[maxm], cur;
int dp[1205][maxn];
vector<int> T;
bool pre[1205][maxn];
struct team
{
    int sam, diff;
} nodes[maxm];
bool init()
{
    scanf("%d%d%d", &n, &p1, &p2);
    if (n == 0 && p1 == 0 && p2 == 0)
        return false;
    tot = p1 + p2;
    for (int i = 0; i < maxm; i++)
        fa[i] = i;
    return true;
}
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
// 1 divine, 2 devil
void solve()
{
    while (n--)
    {
        int u, v;
        char opt[10];
        scanf("%d%d%s", &u, &v, opt);
        if (opt[0] == 'n')
            fa[find(u)] = find(v + tot), fa[find(u + tot)] = find(v);
        else
            fa[find(u)] = find(v), fa[find(u + tot)] = find(v + tot);
    }
    cur = 0;
    memset(cnt, 0, sizeof(cnt));
    for (int i = 1; i <= tot; i++)
    {
        int root = find(i);
        if (cnt[root] == 0 && root <= tot)
            nodes[++cur] = (team){root, find(i + tot)};
        cnt[root]++;
    }
    memset(dp, 0, sizeof(dp));
    //memset(pre, 0, sizeof(pre));
    dp[0][0] = 1;
    for (int i = 1; i <= cur; i++)
        for (int j = 0; j <= p1; j++)
            if (dp[i - 1][j])
            {
                if (j + cnt[nodes[i].sam] <= p1)
                {
                    dp[i][j + cnt[nodes[i].sam]] += dp[i - 1][j];
                    pre[i][j + cnt[nodes[i].sam]] = true;
                }
                if (j + cnt[nodes[i].diff] <= p1)
                {
                    dp[i][j + cnt[nodes[i].diff]] += dp[i - 1][j];
                    pre[i][j + cnt[nodes[i].diff]] = false;
                }
            }
    if (dp[cur][p1] != 1)
    {
        puts("no");
        return;
    }
    int C = p1;
    for (int i = cur; i >= 1; i--)
        if (pre[i][C])
            C -= cnt[nodes[i].sam], T.push_back(nodes[i].sam);
        else
            C -= cnt[nodes[i].diff], T.push_back(nodes[i].diff);
    for (int i = 1; i <= tot; i++)
    {
        int rt = find(i);
        if (find(T.begin(), T.end(), rt) != T.end())
            printf("%d\n", i);
    }
    T.clear();
    printf("end\n");
}
int main()
{
    while (init())
        solve();
    return 0;
}