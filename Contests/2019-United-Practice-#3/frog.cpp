// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int n, dist[MAX_N];
pair<int, int> pts[MAX_N];

int main()
{
    freopen("frog.in", "r", stdin);
    freopen("frog.out", "w", stdout);
    bool flag = true;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &pts[i].first, &pts[i].second), flag &= (pts[i].first == pts[i].second);
    if (flag)
        printf("%d", abs(pts[1].first - pts[n].first)), exit(0);
    // subtask1;
    if (n <= 1000)
    {
        memset(dist, 0x3f, sizeof(dist));
        dist[1] = 0;
        for (int i = 2; i <= n; i++)
            for (int j = i - 1; j >= 1; j--)
                dist[i] = min(dist[i], dist[j] + min(abs(pts[i].first - pts[j].first), abs(pts[i].second - pts[j].second)));
        printf("%d", dist[n]);
    }
    else
    {
        int dis = 0;
        for (int i = 2; i <= n; i++)
            dis += min(abs(pts[i].first - pts[i - 1].first), abs(pts[i].second - pts[i - 1].second));
        printf("%d", dis);
    }

    return 0;
}