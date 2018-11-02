// NOIP2018 T2
#include <iostream>
#include <vector>
#include <queue>

using namespace std;
#define MAX_VAL 1000

// map;
vector< vector<int> > map;
vector<bool> hallysRoom;

int n, m, k;
int pointer_now = 0;
bool flag = true;
int x, y;

void init()
{
    cin >> n >> m >> k;
    hallysRoom.resize(n, false);
    for (int i = 0; i < k; i++)
    {
        int num;
        cin >> num;
        hallysRoom[num] = true;
        flag = false;
    }
    // memset part;
    map.resize(n + 1);
    for (int i = 0; i < n + 1; i++)
        map[i].resize(n + 1, -1);
    // read map;
    for (int i = 0; i < m; i++)
    {
        int src, dst, dg;
        cin >> src >> dst >> dg;
        map[src][dst] = dg;
        map[dst][src] = dg;
    }
    cin >> x >> y;
}

int Djiskra1(int dst)
{
    vector<int> dis(n + 1, MAX_VAL);
    vector<bool> vis(n + 1, false);
    for (int i = 2; i < n + 1; i++)
        if (map[1][i] != -1)
            dis[i] = map[1][i];
    for (int p = 2; p < n + 1; p++)
    {
        int x_ = 0;
        int min_val = MAX_VAL;
        for (int i = 2; i < n + 1; i++)
            if (!vis[i] && dis[i] < min_val)
                min_val = dis[x_ = i];
        vis[x_] = true;
        for (int i = 2; i < n + 1; i++)
            if (map[x_][i] != -1)
                dis[i] = min(dis[i], dis[x_] + map[x_][i]);
    }
    return dis[dst];
}

int Djiskra2(int dst)
{
    vector<int> dis(n + 1, MAX_VAL);
    vector<bool> vis(n + 1, false);
    for (int i = 2; i < n + 1; i++)
        if (map[1][i] != -1 && !hallysRoom[i])
            dis[i] = map[1][i];
    for (int p = 2; p < n + 1; p++)
    {
        int x_ = 0;
        int min_val = MAX_VAL;
        for (int i = 2; i < n + 1; i++)
            if (!vis[i] && dis[i] < min_val && !hallysRoom[i])
                min_val = dis[x_ = i];
        vis[x_] = true;
        for (int i = 2; i < n + 1; i++)
            if (map[x_][i] != -1 && !hallysRoom[i])
                dis[i] = min(dis[i], dis[x_] + map[x_][i]);
    }
    return dis[dst];
}

int main()
{
    init();
    if (flag)
        cout << Djiskra1(x);
    else
        cout << max(Djiskra1(x), Djiskra2(y));
    return 0;
}