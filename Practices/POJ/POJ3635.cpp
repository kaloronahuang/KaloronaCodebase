// POJ3635.cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;
const int maxn = 2200;
#define pr pair<int, int>
int cost[maxn], current = 0, N, M, Q;
int curtcost[maxn][200];
bool vis[maxn][200];
vector<pr> G[maxn];
struct node
{
    int key;
    int city, fuel;
    bool operator<(const node &nd) const
    {
        return key > nd.key;
    }
};
int main()
{
    scanf("%d%d", &N, &M);
    for (int i = 0; i < N; i++)
        scanf("%d", &cost[i]);
    for (int i = 0; i < M; i++)
    {
        int src, dst, w;
        scanf("%d%d%d", &src, &dst, &w);
        G[src].push_back(make_pair(dst, w));
        G[dst].push_back(make_pair(src, w));
    }
    scanf("%d", &Q);
    while (Q--)
    {
        memset(vis, false, sizeof(vis)), memset(curtcost, 0x3f, sizeof(curtcost));
        int src, dst, C;
        bool flag = true;
        scanf("%d%d%d", &C, &src, &dst);
        priority_queue<node> npool;
        npool.push(node{0, src, 0});
        curtcost[src][0] = 0;
        while (!npool.empty())
        {
            node curt = npool.top();
            npool.pop();
            int cc = curt.city, cf = curt.fuel;
            if (vis[cc][cf])
                continue;
            vis[cc][cf] = true;
            if (cc == dst)
            {
                printf("%d\n", curtcost[cc][cf]), flag = false;
                break;
            }
            if (cf < C && curtcost[cc][cf + 1] > curtcost[cc][cf] + cost[cc])
            {
                curtcost[cc][cf + 1] = curtcost[cc][cf] + cost[cc];
                npool.push(node{curtcost[cc][cf + 1], cc, cf + 1});
            }
            int tmp_siz = G[cc].size();
            for (int i = 0; i < tmp_siz; i++)
            {
                pr curte = G[cc][i];
                if (cf >= curte.second &&
                    curtcost[curte.first][cf - curte.second] > curtcost[cc][cf])
                {
                    curtcost[curte.first][cf - curte.second] = curtcost[cc][cf];
                    npool.push(node{curtcost[curte.first][cf - curte.second], curte.first, cf - curte.second});
                }
            }
        }
        if (flag)
            printf("impossible\n");
    }
    return 0;
}