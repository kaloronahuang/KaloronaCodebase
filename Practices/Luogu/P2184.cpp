// P2184.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int nodes[MAX_N][2];
int n, m;

int lowbit(int x) { return x & (-x); }

void update(int id, int x, int d)
{
    for (; x <= n; x += lowbit(x))
        nodes[x][id] += d;
}

int query(int id, int x)
{
    int ret = 0;
    for (; x; x -= lowbit(x))
        ret += nodes[x][id];
    return ret;
}

int main()
{
    scanf("%d%d", &n, &m);
    while (m--)
    {
        int opt, l, r;
        scanf("%d%d%d", &opt, &l, &r);
        if (opt == 1)
            update(0, l, 1), update(1, r, 1);
        else
            printf("%d\n", query(0, r) - query(1, l - 1));
    }
    return 0;
}