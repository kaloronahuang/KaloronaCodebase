// POJ1151.cpp
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 11000;
int n, c[N];
vector<double> mapping;
struct quad
{
    double x, y1, y2, k;
    bool operator<(const quad &qd) const
    {
        return x < qd.x;
    }
} qds[N << 1];
double raw(int x)
{
    return mapping[x];
}
int ripe(double num)
{
    return lower_bound(mapping.begin(), mapping.end(), num) - mapping.begin();
}
int main()
{
    int cnt = 0;
    while (scanf("%d", &n) && n != 0)
    {
        cnt++;
        double ans = 0;
        mapping.resize(0);
        memset(c, 0, sizeof(c));
        for (int i = 1; i <= 2 * n; i += 2)
        {
            scanf("%lf%lf%lf%lf", &qds[i].x, &qds[i].y1, &qds[i + 1].x, &qds[i].y2);
            qds[i].k = 1, qds[i + 1].k = -1;
            qds[i + 1].y2 = qds[i].y2, qds[i + 1].y1 = qds[i].y1;
            mapping.push_back(qds[i].y1), mapping.push_back(qds[i].y2);
        }
        sort(qds + 1, qds + 1 + 2 * n);
        sort(mapping.begin(), mapping.end());
        mapping.erase(unique(mapping.begin(), mapping.end()), mapping.end());
        for (int id = 1; id < 2 * n; id++)
        {
            quad curt = qds[id];
            for (int i = ripe(curt.y1); i < ripe(curt.y2); i++)
                c[i] += curt.k;
            double len = qds[id + 1].x - curt.x;
            int siz = mapping.size();
            for (int i = 0; i < siz; i++)
                if (c[i])
                    ans += len * (raw(i + 1) - raw(i));
        }
        printf("Test case #%d\nTotal explored area: %.2f\n\n", cnt, ans);
    }
    return 0;
}