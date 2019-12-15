// QOJ2016.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, st[20][MAX_N], ans = 0x3f3f3f3f;

int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

int query(int l, int r)
{
    int d = 0, pos = l;
    for (int i = 19; i >= 0; i--)
        if (pos + (1 << i) - 1 <= r)
            d = ((d == 0) ? st[i][pos] : gcd(d, st[i][pos])), pos += (1 << i);
    return d;
}

int main()
{
    scanf("%d", &n);
    int cnt = 0;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &st[0][i]);
        if (st[0][i] == 1)
            cnt++;
    }
    if (cnt > 0)
        printf("%d\n", n - cnt), exit(0);
    int combo = st[0][1];
    for (int i = 2; i <= n; i++)
        combo = gcd(combo, st[0][i]);
    if (combo != 1)
        puts("-1"), exit(0);
    for (int i = 1; i < 20; i++)
        for (int j = 1; j + (1 << i) - 1 <= n; j++)
            st[i][j] = gcd(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
    for (int i = 1; i <= n; i++)
    {
        int l = 1, r = i - 1, res = -1;
        while (l <= r)
        {
            int mid = (l + r) >> 1;
            if (query(mid, i) != 1)
                r = mid - 1;
            else
                l = mid + 1, res = i - mid;
        }
        if (res != -1)
            ans = min(ans, res + n - 1);
    }
    printf("%d\n", ans);
    return 0;
}