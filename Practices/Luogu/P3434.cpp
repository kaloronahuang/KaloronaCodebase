// P3434.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e5 + 200;

int n, m, pre[MAX_N], pips[MAX_N], disks[MAX_N];

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &pips[i]);
    for (int i = 1; i <= m; i++)
        scanf("%d", &disks[i]);
    // prefix max;
    pre[1] = pips[1];
    for (int i = 2; i <= n; i++)
        pre[i] = min(pre[i - 1], pips[i]);
    int stage = n;
    for (int i = 1; i <= m; i++)
    {
        while (pre[stage] < disks[i])
            stage--;
        stage--;
        if (stage == 0)
            printf("%d", 0), exit(0);
    }
    printf("%d", stage + 1);
    return 0;
}