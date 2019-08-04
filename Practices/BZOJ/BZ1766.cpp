// BZ1766.cpp
#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> mapping;
struct point
{
    int x, y;
    bool operator<(const point &pt) const { return x < pt.x || (x == pt.x && y < pt.y); }
} pts[110];

int getRaw(int x, int y) { return mapping[y] - mapping[x] + 1; }

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &pts[i].x, &pts[i].y);
    sort(pts + 1, pts + 1 + n);
    for (int i = 1; i <= n; i++)
        mapping.push_back(pts[i].x), mapping.push_back(pts[i].y);
    sort(mapping.begin(), mapping.end());
    mapping.erase(unique(mapping.begin(), mapping.end()), mapping.end());
    for (int i = 1; i <= n; i++)
        pts[i].x = lower_bound(mapping.begin(), mapping.end(), pts[i].x) - mapping.begin(),
        pts[i].y = lower_bound(mapping.begin(), mapping.end(), pts[i].y) - mapping.begin();

    int field = mapping.size();
    for (int i = 1; i <= field; i++)
        for (int j = i + 1; j <= field; j++)
        {
        }
    return 0;
}