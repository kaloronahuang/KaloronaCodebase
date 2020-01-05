// YBT-OJ1687.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 330, MAX_P = MAX_N * MAX_N, dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
typedef pair<int, int> pii;

int mp[MAX_N][MAX_N], n, m, idx[MAX_N][MAX_N], fa[MAX_P], ptot, pos[MAX_P][2];
bool tag[MAX_P], vis[MAX_N][MAX_N];
pii order[MAX_P], stmp[MAX_P];

int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

int check(int x, int y) { return x <= n && x >= 1 && y <= m && y >= 1; }

void merge(int x, int y) { find(x) != find(y) ? fa[find(x)] = find(y) : 0; }

bool compare(const pii &rhs1, const pii &rhs2) { return mp[rhs1.first][rhs1.second] < mp[rhs2.first][rhs2.second]; }

void bfs(int orgx, int orgy)
{
    queue<pii> q;
    q.push(make_pair(orgx, orgy)), vis[orgx][orgy] = true;
    int org_id = idx[orgx][orgy], tail = 0;
    while (!q.empty())
    {
        pii curt = q.front();
        q.pop(), stmp[++tail] = curt;
        for (int d = 0; d < 4; d++)
        {
            int dstx = curt.first + dx[d], dsty = curt.second + dy[d];
            if (check(dstx, dsty))
            {
                if (mp[dstx][dsty] < mp[curt.first][curt.second])
                    tag[find(org_id)] |= tag[find(idx[dstx][dsty])];
                if (!vis[dstx][dsty] && mp[dstx][dsty] == mp[curt.first][curt.second])
                    q.push(make_pair(dstx, dsty)), vis[dstx][dsty] = true, merge(idx[dstx][dsty], org_id);
            }
        }
    }
    for (int i = 1; i <= tail; i++)
    {
        int x = stmp[i].first, y = stmp[i].second;
        for (int d = 0; d < 4; d++)
        {
            int dstx = x + dx[d], dsty = y + dy[d];
            if (check(dstx, dsty) && vis[dstx][dsty] && tag[find(idx[dstx][dsty])] == false && mp[dstx][dsty] < mp[x][y])
                merge(idx[dstx][dsty], org_id);
        }
    }
}

int main()
{
    scanf("%d%d", &n, &m), n += 2, m += 2;
    for (int i = 2; i <= n - 1; i++)
        for (int j = 2; j <= m - 1; j++)
            scanf("%d", &mp[i][j]);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            idx[i][j] = ++ptot, fa[ptot] = ptot, order[ptot] = make_pair(i, j),
            tag[ptot] = (i == 1 || j == 1 || i == n || j == m), pos[ptot][0] = i, pos[ptot][1] = j;
    sort(order + 1, order + 1 + ptot, compare);
    for (int i = 1; i <= ptot; i++)
        if (!vis[order[i].first][order[i].second])
            bfs(order[i].first, order[i].second);
    for (int i = 2; i <= n - 1; i++, puts(""))
        for (int j = 2; j <= n - 1; j++)
            printf("%d ", mp[pos[find(idx[i][j])][0]][pos[find(idx[i][j])][1]] - mp[i][j]);
    return 0;
}