// CF1172A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int n, ai[MAX_N], bi[MAX_N], pos[MAX_N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]), pos[ai[i]] = 0;
    for (int i = 1; i <= n; i++)
        scanf("%d", &bi[i]), pos[bi[i]] = i;
    if (pos[1])
    {
        int i, j;
        for (i = 2; pos[i] == pos[1] + i - 1; i++)
            ;
        if (pos[i - 1] == n)
        {
            for (j = i; j <= n && pos[j] <= j - i; j++)
                ;
            if (j > n)
            {
                printf("%d\n", n - i + 1);
                return 0;
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
        ans = max(ans, pos[i] - i + n + 1);
    printf("%d\n", ans);
    return 0;
}