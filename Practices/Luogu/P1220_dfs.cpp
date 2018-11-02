// P1220_DFS.cpp
// luogu-judger-enable-o2
// P1220.cpp
#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

int n, c;
int lightPos[60];
int walt[60];
bool vis[60];

int ans = 2e9;

void DFS(int curt, int total_sum, int bolbs, int tot, int father)
{
    if (tot >= ans)
        return;
    if (bolbs == n)
    {
        ans = min(ans, tot);
        return;
    }
    if (curt == 0 || curt > n)
        return;
    int factor = total_sum - walt[curt];
    if (vis[curt])
    {
        // go up;
        if (curt + 1 != father)
            DFS(curt + 1, total_sum, bolbs, tot + total_sum * abs(lightPos[curt] - lightPos[curt + 1]), curt);
        // go down;
        if (curt - 1 != father)
            DFS(curt - 1, total_sum, bolbs, tot + total_sum * abs(lightPos[curt] - lightPos[curt - 1]), curt);
        return;
    }
    vis[curt] = true;
    if (curt < n)
        DFS(curt + 1, factor, bolbs + 1, tot + factor * abs(lightPos[curt] - lightPos[curt + 1]), -1);
    if (curt > 0)
        DFS(curt - 1, factor, bolbs + 1, tot + factor * abs(lightPos[curt] - lightPos[curt - 1]), -1);
    vis[curt] = false;
}

void solve()
{
    memset(vis, false, sizeof(vis));
    int total = 0;
    cin >> n >> c;
    for (int i = 1; i <= n; i++)
        cin >> lightPos[i] >> walt[i], total += walt[i];
    DFS(c, total, 0, 0, -1);
    cout << ans;
}

int main()
{
    solve();
    return 0;
}