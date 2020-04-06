// A.cpp
#include <bits/stdc++.h>

using namespace std;

int n;

int main()
{
    scanf("%d", &n);
    if (n & 1)
    {
        printf("%lld\n", 1LL * n * (n + 1) - 1);
        int x = 1, y = n + 1;
        int rd = (n - 1) >> 1;
        for (int i = 1; i <= n; i++, x++)
            printf("%d %d\n", x, y);
        x--;
        while (rd--)
        {
            y--, x--;
            printf("%d %d\n", x, y);
            for (int i = 1, dy = -1; i <= n - 2; i++, dy = 0 - dy)
            {
                y += dy, x--;
                printf("%d %d\n", x, y);
            }
            x--;
            for (int i = 1, dy = 1; i <= n - 1; i++, dy = 0 - dy)
            {
                y += dy, x++;
                printf("%d %d\n", x, y);
            }
            x++, y++;
            printf("%d %d\n", x, y);
            y--;
            printf("%d %d\n", x, y);
        }
        y--, printf("%d %d\n", x, y);
        for (int i = n - 1; i >= 1; i--)
            printf("%d %d\n", i, 1);
    }
    else
    {
        printf("%lld\n", 1LL * n * (n + 1) - 1);
        int x = n, y = 1, rd = n >> 1;
        for (int i = 1; i <= n - 1; i++)
            printf("%d %d\n", x, y), x--;
        printf("%d %d\n", x, y);
        while (rd--)
        {
            y++;
            printf("%d %d\n", x, y);
            for (int i = 1, dy = 1; i <= n - 1; i++, dy = -dy)
            {
                y += dy, x++;
                printf("%d %d\n", x, y);
            }
            y--;
            printf("%d %d\n", x, y);
            for (int i = 1, dy = 1; i <= n - 1; i++, dy = -dy)
            {
                y += dy, x--;
                printf("%d %d\n", x, y);
            }
        }
    }

    return 0;
}