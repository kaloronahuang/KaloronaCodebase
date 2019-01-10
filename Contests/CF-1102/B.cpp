// B.cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <bitset>
using namespace std;
bitset<5010> bi[5010];
int n, arr[5010], k, color[5010], mx;
int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d", &arr[i]), bi[arr[i]].set(i, true), mx = max(mx, arr[i]);
    for (int i = 1; i <= mx; i++)
        if (bi[i].count() > k)
            printf("NO"), exit(0);
    int curt = 0;
    for (int i = 1; i <= mx; i++)
    {
        int col = 0;
        for (int j = 1; j <= n; j++)
            if (bi[i][j])
            {
                if (curt == k)
                    color[j] = ++col, col %= k, bi[i].set(j, false);
                else
                    color[j] = ++curt, bi[i].set(j, false);
            }
    }
    printf("YES\n");
    for (int i = 1; i <= n; i++)
        printf("%d ", color[i]);
    return 0;
}