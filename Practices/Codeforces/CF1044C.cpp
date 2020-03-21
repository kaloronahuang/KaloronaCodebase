// CF1044C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e5 + 200;

typedef long long ll;

int n;
ll xi[MAX_N], yi[MAX_N], rect[4][2];

ll dist(int x, int y) { return abs(rect[x][0] - rect[y][0]) + abs(rect[x][1] - rect[y][1]); }

ll distRPT(int x, int y) { return abs(rect[x][0] - xi[y]) + abs(rect[x][1] - yi[y]); }

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld%lld", &xi[i], &yi[i]);
        if (i == 1)
            for (int j = 0; j < 4; j++)
                rect[j][0] = xi[i], rect[j][1] = yi[i];
        else
        {
            if (xi[i] > rect[0][0])
                rect[0][0] = xi[i], rect[0][1] = yi[i];
            if (yi[i] < rect[1][1])
                rect[1][0] = xi[i], rect[1][1] = yi[i];
            if (xi[i] < rect[2][0])
                rect[2][0] = xi[i], rect[2][1] = yi[i];
            if (yi[i] > rect[3][1])
                rect[3][0] = xi[i], rect[3][1] = yi[i];
        }
    }
    ll ans = 0;
    for (int i = 0; i <= 3; i++)
        for (int j = 0; j <= 3; j++)
            if (i != j)
                for (int k = 1; k <= n; k++)
                    ans = max(ans, dist(i, j) + distRPT(i, k) + distRPT(j, k));
    printf("%lld ", ans), ans = 0;
    for (int i = 0; i <= 3; i++)
        ans += dist(i, (i + 1) % 4);
    for (int i = 4; i <= n; i++)
        printf("%lld ", ans);
    puts("");
    return 0;
}