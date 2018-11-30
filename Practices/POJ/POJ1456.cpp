// POJ1456.cpp
#include <iostream>
#include <queue>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 10005;
int n;
bool vis[maxn];
struct commodity
{
    int p, d;
    bool operator<(const commodity &cmd) const
    {
        return (p > cmd.p) || ((p == cmd.p) && (d > cmd.d));
    }
} cms[maxn];
int main()
{
    while (scanf("%d", &n) != EOF)
    {
        for (int i = 0; i < n; i++)
            scanf("%d%d", &cms[i].p, &cms[i].d);
        sort(cms, cms + n);
        fill(vis, vis + maxn, false);
        int ans = 0;
        for (int i = 0, j; i < n; i++)
        {
            commodity cmd = cms[i];
            for (j = cmd.d; j > 0 && vis[j]; j--)
                ;
            if (j)
                vis[j] = true, ans += cmd.p;
        }
        printf("%d\n", ans);
    }
    return 0;
}