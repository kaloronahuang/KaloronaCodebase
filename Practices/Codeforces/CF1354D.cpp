// CF1354D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

int n, q, nodes[MAX_N];

int lowbit(int x) { return x & (-x); }

void update(int x, int d)
{
    for (; x <= n; x += lowbit(x))
        nodes[x] += d;
}

int query(int x, int ret = 0)
{
    for (; x; x -= lowbit(x))
        ret += nodes[x];
    return ret;
}

int main()
{
    scanf("%d%d", &n, &q);
    for (int i = 1, val; i <= n; i++)
        scanf("%d", &val), update(val, 1);
    while (q--)
    {
        int x;
        scanf("%d", &x);
        if (x > 0)
            update(x, 1);
        else
        {
            int l = 1, r = n, res;
            while (l <= r)
            {
                int mid = (l + r) >> 1;
                if (query(mid) >= -x)
                    r = mid - 1, res = mid;
                else
                    l = mid + 1;
            }
            update(res, -1);
        }
    }
    for (int i = 1; i <= n; i++)
        if (query(i) - query(i - 1) > 0)
            printf("%d\n", i), exit(0);
    puts("0");
    return 0;
}