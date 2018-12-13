// POJ1167.cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 500;
int n, tmp, siz, ans = 17;
struct gap
{
    int gaps, sttime, stats;
} ints[maxn];
bool cmp(gap a, gap b)
{
    return a.stats > b.stats;
}
int vis[maxn];
bool check(int start, int interval)
{
    for (register int i = start; i < 60; i += interval)
        if (!vis[i])
            return false;
    return true;
}
inline void dfs(int st, int dep, int remain)
{
    if (remain / ints[st].stats + dep >= ans)
        return;
    if (!remain)
    {
        ans = min(ans, dep);
        return;
    }
    for (register int i = st; i <= siz; i++)
        if (check(ints[i].sttime, ints[i].gaps))
        {
            for (register int tim = ints[i].sttime; tim < 60; tim += ints[i].gaps)
                vis[tim]--;
            dfs(i, dep + 1, remain - ints[i].stats);
            for (register int tim = ints[i].sttime; tim < 60; tim += ints[i].gaps)
                vis[tim]++;
        }
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &tmp), vis[tmp]++;
    for (int i = 0; i < 30; i++)
        for (int j = i + 1; i + j < 60; j++)
            if (check(i, j))
            {
                ints[++siz].gaps = j, ints[siz].sttime = i;
                // calc the stations upnext;
                for (int k = ints[siz].sttime; k < 60; k += ints[siz].gaps)
                    ints[siz].stats++;
            }
    sort(ints + 1, ints + 1 + siz, cmp);
    dfs(1, 0, n);
    printf("%d\n", ans);
    return 0;
}