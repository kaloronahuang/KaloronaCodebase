// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e5 + 2000;

int st[30][MAX_N], sum[30][MAX_N], n, m;

int query(int l, int r)
{
    if (l > r)
        return 0;
    int len = log2(r - l + 1);
    return sum[len][l];
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &st[0][i]), sum[0][i] = 0;
    for (int i = 1; (1 << i) <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            sum[i][j] = sum[i - 1][j] + sum[i - 1][j + (1 << (i - 1))];
            st[i][j] = st[i - 1][j] + st[i - 1][j + (1 << (i - 1))];
            if (st[i][j] >= 10)
                st[i][j] %= 10, sum[i][j]++;
        }
    }
    scanf("%d", &m);
    while (m--)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        printf("%d\n", query(l, r));
    }
    return 0;
}