// P2742.cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>
#define pr pair<double, double>
using namespace std;
int n;
vector<pr> points;
deque<int> prs;
double getDist(pr a, pr b)
{
    return sqrt((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second));
}
bool judge(int a, int b, int idx)
{
    return (points[a].second - points[b].second) * (points[b].first - points[idx].first) >
           (points[a].first - points[b].first) * (points[b].second - points[idx].second);
}
int main()
{
    double ans = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        double x, y;
        scanf("%lf%lf", &x, &y);
        points.push_back(make_pair(x, y));
    }
    sort(points.begin(), points.end());
    prs.push_front(0), prs.push_front(1);
    for (int i = 2; i < n; i++)
    {
        while (prs.size() > 1 && !judge(prs[0], prs[1], i))
            prs.pop_front();
        prs.push_front(i);
    }
    for (int i = 0; i < prs.size() - 1; i++)
        ans += getDist(points[prs[i]], points[prs[i + 1]]);
    prs.clear();
    prs.push_front(0), prs.push_front(1);
    for (int i = 2; i < n; i++)
    {
        while (prs.size() > 1 && judge(prs[0], prs[1], i))
            prs.pop_front();
        prs.push_front(i);
    }
    for (int i = 0; i < prs.size() - 1; i++)
        ans += getDist(points[prs[i]], points[prs[i + 1]]);
    printf("%.2lf", ans);
    return 0;
}