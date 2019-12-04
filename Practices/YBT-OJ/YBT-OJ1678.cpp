// YBT-OJ1678.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int n, pos[MAX_N], di[MAX_N], q, order[MAX_N], rk[MAX_N], tot1, tot2, d1[MAX_N], d2[MAX_N];

bool compare(int a, int b) { return pos[a] < pos[b]; }

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &pos[i]), order[i] = i;
    sort(order + 1, order + 1 + n, compare);
    for (int i = 1; i <= n; i++)
        rk[order[i]] = i;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &di[i]);
        if (di[i] == 0)
            d1[++tot1] = pos[i];
        else
            d2[++tot2] = pos[i];
    }
    sort(d1 + 1, d1 + 1 + tot1);
    sort(d2 + 1, d2 + 1 + tot2);
    scanf("%d", &q);
    while (q--)
    {
        int ki, ti;
        scanf("%d%d", &ki, &ti), ki = rk[ki + 1];
        int l = max(0, ki - tot2), r = min(tot1, ki), x = 0;
        while (l <= r)
        {
            int mid = (l + r) >> 1;
            if (ki - mid == tot2 || d1[mid] - ti <= d2[ki - mid + 1] + ti)
                l = mid + 1;
            else
                r = mid - 1;
        }
        x = r;
        if (x == 0)
            printf("%d\n", d2[ki] + ti);
        else if (x == ki)
            printf("%d\n", d1[ki] - ti);
        else
            printf("%d\n", max(d1[x] - ti, d2[ki - x] + ti));
    }
    return 0;
}