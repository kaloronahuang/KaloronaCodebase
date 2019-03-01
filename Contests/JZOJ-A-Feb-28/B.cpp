// B.cpp
#include <bits/stdc++.h>
using namespace std;
int ai[4], bi[4], n, tmpx;
int jump(int &x, int &y, int k)
{
    while (k)
    {
        if (x == y)
            break;
        if (x > y)
        {
            if (k < x / y)
            {
                x -= k * y;
                break;
            }
            k -= x / y;
            if (x % y == 0)
            {
                x = y;
                break;
            }
            x -= (x / y) * y;
        }
        else
        {
            if (k < y / x)
            {
                y -= k * x;
                break;
            }
            k -= y / x;
            if (y % x == 0)
            {
                y = x;
                break;
            }
            y -= (y / x) * x;
        }
    }
}
int dep(int x, int y, int &root)
{
    int ans = 0, tmp;
    root = x;
    while (true)
    {
        if (x < y)
            swap(x, y);
        if (x % y == 0)
        {
            ans += x / y - 1, root = y;
            break;
        }
        tmp = y, ans += x / y, y = x % y, x = tmp;
    }
    return ans;
}
int lca(int a1, int a2, int b1, int b2)
{
    int d1 = dep(a1, a2, tmpx), d2 = dep(b1, b2, tmpx);
    if (d1 < d2)
        swap(a1, b1), swap(a2, b2), swap(d1, d2);
    int ans = 0;
    for (int i = log2(d1 - d2); i >= 0; i--)
    {
        int l = a1, r = a2;
        jump(l, r, (1 << i));
        int now = dep(l, r, tmpx);
        if (now >= d2)
            d1 = now, a1 = l, a2 = r, ans += (1 << i);
        if (now == d2)
            break;
    }
    if (a1 == b1 && b2 == a2)
        return ans;
    for (int i = log2(d1); i >= 0; i--)
    {
        int l = a1, r = a2, x = b1, y = b2;
        jump(l, r, 1 << i), jump(x, y, 1 << i);
        if (l == x && r == y)
            continue;
        a1 = l, a2 = r, b1 = x, b2 = y, ans += 2 * (1 << i);
    }
    return ans + 2;
}
int main()
{
    n = 3;
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    for (int i = 1; i <= n; i++)
        scanf("%d", &bi[i]);
    sort(ai + 1, ai + 4), sort(bi + 1, bi + 4);
    int a1 = ai[2] - ai[1], a2 = ai[3] - ai[2], rt1;
    int b1 = bi[2] - bi[1], b2 = bi[3] - bi[2], rt2;
    dep(a1, a2, rt1), dep(b1, b2, rt2);
    if (rt1 != rt2)
        printf("NO"), exit(0);
    printf("YES\n%d", lca(a1, a2, b1, b2));
    return 0;
}