// ARC092A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 210;

int n;
bool enabled[MAX_N];

struct point
{
    int x, y, typ;
    bool operator<(const point &rhs) const { return x < rhs.x; }
} pts[MAX_N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= (n << 1); i++)
        scanf("%d%d", &pts[i].x, &pts[i].y), pts[i].typ = i > n;
    sort(pts + 1, pts + 1 + (n << 1));
    int ans = 0;
    for (int i = 1; i <= (n << 1); i++)
        if (pts[i].typ == 1)
        {
            int id = -1;
            for (int j = 1; j < i; j++)
                if (!enabled[j] && pts[j].typ == 0 && pts[j].y < pts[i].y && (id == -1 || pts[j].y > pts[id].y))
                    id = j;
            if (id != -1)
                enabled[id] = true, ans++;
        }
    printf("%d\n", ans);
    return 0;
}