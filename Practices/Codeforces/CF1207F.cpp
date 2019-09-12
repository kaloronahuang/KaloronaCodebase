// CF1207F.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e5 + 200, MAX_K = 750;

int sum[MAX_K][MAX_K], ai[MAX_N];

int main()
{
    int q;
    scanf("%d", &q);
    while (q--)
    {
        int opt, x, y;
        scanf("%d%d%d", &opt, &x, &y);
        if (opt == 1)
        {
            ai[x] += y;
            for (int i = 1; i < MAX_K; i++)
                sum[i][x % i] += y;
        }
        else if (x >= MAX_K)
        {
            int ans = 0;
            for (int i = y; i <= 500000; i += x)
                ans += ai[i];
            printf("%d\n", ans);
        }
        else
            printf("%d\n", sum[x][y]);
    }
    return 0;
}