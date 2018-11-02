// P1433.cpp
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

double ans = 1e9;
bool vis[20];
double xi[20];
double yi[20];
int n;

double getDist(double srcx, double srcy, double dstx, double dsty)
{
    return sqrt(pow(srcx - dstx, 2) + pow(srcy - dsty, 2));
}

void DFS(int idx, double pre)
{
    if (pre > ans)
        return;
    bool flag = true;
    vis[idx] = true;
    for (int i = 0; i < n; i++)
        if (!vis[i])
            flag = false, DFS(i, pre + getDist(xi[idx], yi[idx], xi[i], yi[i]));
    vis[idx] = false;
    if (flag)
        ans = min(ans, pre);
}

int main()
{
    cin >> n;
    fill(vis, vis + 20, false);
    for (int i = 0; i < n; i++)
        cin >> xi[i] >> yi[i];
    xi[19] = yi[19] = 0;
    DFS(19, 0);
    cout << fixed << setprecision(2) << ans;
    return 0;
}