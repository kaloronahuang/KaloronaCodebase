// CF1204C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 110;

int n, m, dist[MAX_N][MAX_N], bi[(int)1e6 + 200];
char mp[MAX_N][MAX_N];
bool vis[MAX_N];

int main()
{
    memset(dist, 0x3f, sizeof(dist));
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%s", mp[i] + 1);
        for (int j = 1; j <= n; j++)
            if (mp[i][j] == '1')
                dist[i][j] = 1;
        dist[i][i] = 0;
    }
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
    vector<int> ans;
    scanf("%d", &m);
    for (int i = 1; i <= m; i++)
        scanf("%d", &bi[i]);

    ans.push_back(bi[1]);
    int i = 1, j = 3;
    for (int k = 2; k <= m - 1; k++)
    {
        if (dist[bi[i]][bi[j]] >= dist[bi[i]][bi[k]] + dist[bi[k]][bi[j]])
            j++;
        else
            i = k, j++, ans.push_back(bi[k]);
    }
    ans.push_back(bi[m]);
    printf("%d\n", ans.size());
    for (int i = 0, siz = ans.size(); i < siz; i++)
        printf("%d ", ans[i]);
    return 0;
}