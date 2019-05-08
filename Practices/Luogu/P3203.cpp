// P3203.cpp
#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 201000;

int n, q, m, force[MAX_N], lft[MAX_N], rig[MAX_N], tot, aff[MAX_N], oblk[MAX_N], tarpt[MAX_N];

void update(int l, int r)
{
    for (int i = r; i >= l; i--)
        if (i + force[i] > rig[aff[i]])
            oblk[i] = 1, tarpt[i] = i + force[i];
        else
            oblk[i] = oblk[i + force[i]] + 1, tarpt[i] = tarpt[i + force[i]];
}

int main()
{
    scanf("%d", &n), m = sqrt(n), tot = n / m;
    for (int i = 1; i <= n; i++)
        scanf("%d", &force[i]);
    for (int i = 1; i <= tot; i++)
        lft[i] = rig[i - 1] + 1, rig[i] = lft[i] + m - 1;
    if (rig[tot] < n)
        lft[++tot] = rig[tot - 1] + 1, rig[tot] = n;
    int s = 1;
    for (int i = 1; i <= n; i++)
    {
        if (i > rig[s])
            s++;
        aff[i] = s;
    }
    update(1, n);
    scanf("%d", &q);
    while (q--)
    {
        int a, b, c;
        scanf("%d%d", &a, &b), b++;
        if (a == 1)
        {
            int pos = b, ans = 0;
            for (int i = aff[pos]; i <= tot && pos <= n; i++)
                ans += oblk[pos], pos = tarpt[pos];
            printf("%d\n", ans);
        }
        else
        {
            scanf("%d", &c), force[b] = c;
            update(lft[aff[b]], rig[aff[b]]);
        }
    }
    return 0;
}