// POJ2318.cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

using namespace std;

const int MAX_N = 5050;

struct vec
{
    double x, y;
    vec(double _x = 0, double _y = 0) : x(_x), y(_y) {}
    vec operator+(const vec &rhs) { return vec(x + rhs.x, y + rhs.y); }
    vec operator-(const vec &rhs) { return vec(x - rhs.x, y - rhs.y); }
    double operator*(const vec &rhs) const { return x * rhs.x + y * rhs.y; }
    double operator^(const vec &rhs) const { return x * rhs.y - y * rhs.x; }
    vec operator/(const double &rhs) const { return vec(x / rhs, y / rhs); }
    double len2() { return x * x + y * y; }
    double len() { return sqrt(len2()); }
} dirs[MAX_N];

int n, m, x1_, y1_, x2_, y2_, cnt[MAX_N], ui[MAX_N], di[MAX_N];

int main()
{
    while (scanf("%d", &n) != EOF && n != 0)
    {
        memset(cnt, 0, sizeof(cnt));
        scanf("%d%d%d%d%d", &m, &x1_, &y1_, &x2_, &y2_);
        dirs[1] = vec(x1_, y1_) - vec(x1_, y2_), dirs[n + 2] = vec(x2_, y1_) - vec(x2_, y2_);
        ui[1] = x1_, ui[n + 2] = x2_, di[1] = x1_, di[n + 2] = x2_;
        for (int i = 2; i <= n + 1; i++)
            scanf("%d%d", &ui[i], &di[i]), dirs[i] = vec(ui[i], y1_) - vec(di[i], y2_);
        for (int i = 1, x, y; i <= m; i++)
        {
            scanf("%d%d", &x, &y);
            for (int j = 1; j < n + 2; j++)
            {
                vec lft = vec(x, y) - vec(di[j], y2_), rig = vec(x, y) - vec(di[j + 1], y2_);
                // double lftcross = (lft ^ dirs[j]), rigcross = (rig ^ dirs[j + 1]);
                if ((lft ^ dirs[j]) * (rig ^ dirs[j + 1]) < 0)
                {
                    cnt[j - 1]++;
                    break;
                }
                if (j == n + 1)
                    continue;
            }
        }
        for (int i = 0; i <= n; i++)
            printf("%d: %d\n", i, cnt[i]);
        puts("");
    }
    return 0;
}