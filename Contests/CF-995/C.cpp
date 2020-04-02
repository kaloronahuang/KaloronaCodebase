// C.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 1e5 + 200, RANGE = 1.5e6;

int n, ans[MAX_N];

struct vec
{
    ll x, y;
    int id;
    vec operator+(const vec &rhs) { return vec{x + rhs.x, y + rhs.y}; }
    vec operator-(const vec &rhs) { return vec{x - rhs.x, y - rhs.y}; }
} pts[MAX_N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld%lld", &pts[i].x, &pts[i].y), pts[i].id = i;
    while (true)
    {
        random_shuffle(pts + 1, pts + 1 + n);
        vec curt = vec{0, 0};
        for (int i = 1; i <= n; i++)
        {
            if ((curt + pts[i]).x * (curt + pts[i]).x + (curt + pts[i]).y * (curt + pts[i]).y <= (curt - pts[i]).x * (curt - pts[i]).x + (curt - pts[i]).y * (curt - pts[i]).y)
                curt = curt + pts[i], ans[pts[i].id] = 1;
            else
                curt = curt - pts[i], ans[pts[i].id] = -1;
        }
        if (curt.x * curt.x + curt.y * curt.y <= 1LL * RANGE * RANGE)
        {
            for (int i = 1; i <= n; i++)
                printf("%d ", ans[i]);
            puts("");
            return 0;
        }
    }
    return 0;
}