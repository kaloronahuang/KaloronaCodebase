// CF1044D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int q, lastans;
map<int, int> fa, weight;

int find(int x)
{
    if (fa.count(x) == 0)
        return x;
    int up = find(fa[x]);
    weight[x] ^= weight[fa[x]];
    fa[x] = up;
    return up;
}

int main()
{
    scanf("%d", &q);
    while (q--)
    {
        int opt, l, r, x;
        scanf("%d", &opt);
        if (opt == 1)
        {
            scanf("%d%d%d", &l, &r, &x), l ^= lastans, r ^= lastans, x ^= lastans;
            if (l > r)
                swap(l, r);
            l--;
            int lf = find(l), rf = find(r);
            if (lf != rf)
                fa[rf] = lf, weight[rf] = x ^ weight[l] ^ weight[r];
        }
        else
        {
            scanf("%d%d", &l, &r), l ^= lastans, r ^= lastans;
            if (l > r)
                swap(l, r);
            l--;
            int lf = find(l), rf = find(r);
            if (lf != rf)
                puts("-1"), lastans = 1;
            else
                printf("%d\n", lastans = weight[l] ^ weight[r]);
        }
    }
    return 0;
}