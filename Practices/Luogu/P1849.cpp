// P1849.cpp
#include <bits/stdc++.h>
#define pr pair<int, int>
#define ppr pair<int, pr>

using namespace std;

const int MAX_N = 1010, dx[4] = {0, 0, -1, 1}, dy[4] = {-1, 1, 0, 0};

int mp[MAX_N][MAX_N], n, sx, sy, tmpx, tmpy;
bool vis[MAX_N][MAX_N];

int main()
{
    scanf("%d%d%d", &n, &sx, &sy);
    while (n--)
        scanf("%d%d", &tmpx, &tmpy), mp[tmpx][tmpy]++;
    priority_queue<ppr> pq;
    pq.push(make_pair(0, make_pair(-sx, -sy)));
    vis[sx][sy] = true;
    while (!pq.empty())
    {
        pr pos = pq.top().second;
        int dist = -pq.top().first;
        pq.pop();
        if (-pos.first == 0 && -pos.second == 0)
            printf("%d", dist), exit(0);
        for (int i = 0; i < 4; i++)
        {
            int dstx = -pos.first + dx[i], dsty = -pos.second + dy[i];
            if (dstx < 0 || dsty < 0 || dstx >= MAX_N || dsty >= MAX_N || vis[dstx][dsty])
                continue;
            pq.push(make_pair(-dist - mp[dstx][dsty], make_pair(-dstx, -dsty)));
            vis[dstx][dsty] = true;
        }
    }
    return 0;
}