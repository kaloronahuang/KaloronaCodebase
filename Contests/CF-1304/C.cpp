// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 110;

int T, n, m;

struct tup
{
    int t, l, r;
    bool operator<(const tup &rhs) const { return t < rhs.t; }
} tups[MAX_N];

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++)
            scanf("%d%d%d", &tups[i].t, &tups[i].l, &tups[i].r);
        sort(tups + 1, tups + 1 + n);
        int pre_l = m, pre_r = m, pre_t = 0;
        bool flag = true;
        for (int i = 1; i <= n; i++)
        {
            int delta = tups[i].t - pre_t;
            pre_l -= delta, pre_r += delta;
            pre_l = max(pre_l, tups[i].l), pre_r = min(pre_r, tups[i].r), pre_t = tups[i].t;
            if (pre_l > pre_r)
            {
                puts("NO"), flag = false;
                break;
            }
        }
        if (flag)
            puts("YES");
    }
    return 0;
}