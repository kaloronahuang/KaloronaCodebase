// YBT-OJ1686.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 55, MAX_P = MAX_N * MAX_N, MAX_LEN = 10010, dirx[4] = {0, 0, -1, 1}, diry[4] = {1, -1, 0, 0}, INF = 0x3f3f3f3f;

int dist[MAX_P], id[MAX_N][MAX_N], ptot, n, m, len, ways[MAX_P][4], current_dep, nxt_dist[MAX_P];
char mp[MAX_N][MAX_N], target[MAX_LEN], str[MAX_P];
bool vis[MAX_P], gone[MAX_P];

int check(int x, int y) { return x <= n && x >= 1 && y <= m && y >= 1; }

bool compare(const int &rhs1, const int &rhs2) { return dist[rhs1] < dist[rhs2]; }

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%s", mp[i] + 1);
    scanf("%s", target + 1), len = strlen(target + 1), target[++len] = '*';
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            id[i][j] = ++ptot, str[id[i][j]] = mp[i][j];
    memset(ways, 0x3f, sizeof(ways));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            for (int d = 0; d < 4; d++)
            {
                // to where?
                int dstx = i + dirx[d], dsty = j + diry[d];
                while (check(dstx, dsty) && str[id[dstx][dsty]] == str[id[i][j]])
                    dstx += dirx[d], dsty += diry[d];
                if (check(dstx, dsty) && str[id[dstx][dsty]] != str[id[i][j]])
                    ways[id[i][j]][d] = id[dstx][dsty];
            }
    deque<int> q1, q2;
    q2.push_back(id[1][1]);
    for (int ptr = 1, pt; ptr <= len; ptr++)
    {
        memset(vis, 0, sizeof(vis));
        memset(gone, 0, sizeof(gone));
        for (int idx = 0, siz = q2.size(); idx < siz; idx++)
            vis[q2[idx]] = true;
        while ((!q1.empty()) || (!q2.empty()))
        {
            if (q1.empty())
                pt = q2.front(), q2.pop_front();
            else if (q2.empty())
                pt = q1.front(), q1.pop_front();
            else
                pt = (dist[q1.front()] < dist[q2.front()]) ? q1.front() : q2.front(),
                (dist[q1.front()] < dist[q2.front()]) ? q1.pop_front() : q2.pop_front();
            if (str[pt] == target[ptr])
                nxt_dist[pt] = dist[pt] + 1, gone[pt] = true;
            for (int d = 0; d < 4; d++)
                if (ways[pt][d] != INF && !vis[ways[pt][d]])
                    dist[ways[pt][d]] = dist[pt] + 1, vis[ways[pt][d]] = true, q1.push_back(ways[pt][d]);
        }
        // reset;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                if (gone[id[i][j]])
                    dist[id[i][j]] = nxt_dist[id[i][j]], q2.push_back(id[i][j]);
        sort(q2.begin(), q2.end(), compare);
    }
    int ans = 0x3f3f3f3f;
    for (int idx = 0, siz = q2.size(); idx < siz; idx++)
        ans = min(ans, dist[q2[idx]]);
    printf("%d\n", ans);
    return 0;
}