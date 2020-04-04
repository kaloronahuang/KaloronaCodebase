// A.cpp
#include <bits/stdc++.h>

using namespace std;

int xi[5], yi[5], ai[5], bi[5];

int main()
{
    for (int i = 1; i <= 4; i++)
        scanf("%d%d", &xi[i], &yi[i]);
    for (int i = 1; i <= 4; i++)
        scanf("%d%d", &ai[i], &bi[i]);
    sort(xi + 1, xi + 1 + 4);
    sort(yi + 1, yi + 1 + 4);
    sort(ai + 1, ai + 1 + 4);
    sort(bi + 1, bi + 1 + 4);
    for (int i = xi[1]; i <= xi[4]; i++)
    {
        for (int j = yi[1]; j <= yi[4]; j++)
        {
            int t = bi[2], l = 0;
            int t1 = bi[2], l1 = 0;
            for (int k = ai[1]; k <= ai[2]; k++)
            {
                if (i == k && (j >= t - l && j <= t + l))
                    puts("YES"), exit(0);
                l++;
            }
            for (int k = ai[4]; k >= ai[2]; k--)
            {
                if (i == k && (j >= t1 - l1 && j <= t1 + l1))
                    puts("YES"), exit(0);
                l1++;
            }
        }
    }
    puts("NO");
    return 0;
}