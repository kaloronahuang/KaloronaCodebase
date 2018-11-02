// peanut.cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

const int maxn = 21;
const int maxt = 2020;
int M, N, K;
int map[maxn][maxn];
bool vis[maxn];
int px[maxn];
int py[maxn];
int pw[maxn];
int cur = 0;
int ans = 0;

int getDist(int idx1, int idx2)
{
    return abs(px[idx1] - px[idx2]) + abs(py[idx1] - py[idx2]);
}

bool DFS(int idx, int pre, int tim)
{
    bool flag = false;
    if (tim + 1 > K)
        return false;
    vis[idx] = true;
    for (int i = 0; i < cur; i++)
    {
        if (vis[i])
            continue;
        if (!DFS(i, pw[i] + pre, tim + 1 + getDist(idx, i)))
            ans = max(ans, pw[i] + pre), flag = true;
        if (!DFS(i, pre, tim + getDist(idx, i)))
            ans = max(ans, pre), flag = true;
    }
    vis[idx] = false;
    return flag;
}

int main()
{
    //freopen("peanut.in", "r", stdin);
    //freopen("peanut.out", "w", stdout);
    fill(vis, vis + maxn, false);
    cin >> M >> N >> K;
    for (int i = 1; i <= M; i++)
        for (int j = 1; j <= N; j++)
        {
            cin >> map[i][j];
            if (map[i][j] != 0)
            {
                px[cur] = i, py[cur] = j;
                pw[cur++] = map[i][j];
            }
        }
    for (int i = 0; i < cur; i++)
        DFS(i, 0, 1);
    cout << ans;
    return 0;
}