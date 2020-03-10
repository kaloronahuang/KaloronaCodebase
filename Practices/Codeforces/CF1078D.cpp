// CF1078D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e5 + 200;

int n, ai[MAX_N], lft[20][MAX_N], rig[20][MAX_N], log2_[MAX_N];

struct ST
{
    int table[20][MAX_N], val[MAX_N], typ;

    int gmax(int x, int y) { return val[x] > val[y] ? x : y; }

    void build(int *arr, int len, int type)
    {
        typ = type;
        for (int i = 1; i <= len; i++)
            table[0][i] = i, val[i] = typ * arr[i];
        for (int i = 1; i <= 19; i++)
            for (int j = 1; j + (1 << i) - 1 <= len; j++)
                table[i][j] = gmax(table[i - 1][j], table[i - 1][j + (1 << (i - 1))]);
    }

    int query(int l, int r)
    {
        int d = log2_[r - l + 1];
        return gmax(table[d][l], table[d][r - (1 << d) + 1]);
    }
} lrmq, rrmq;

int main()
{
    scanf("%d", &n);
    for (int i = 2; i <= 3 * n; i++)
        log2_[i] = log2_[i >> 1] + 1;
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]), ai[i + n] = ai[i + (n << 1)] = ai[i];
    if (n == 1)
        return puts("0"), 0;
    for (int i = 1; i <= 3 * n; i++)
        lft[0][i] = max(1, i - ai[i]), rig[0][i] = min(3 * n, i + ai[i]);
    for (int i = 0; i <= log2_[3 * n]; i++)
        lft[i][1] = 1, rig[i][3 * n] = 3 * n;
    lrmq.build(lft[0], 3 * n, -1), rrmq.build(rig[0], 3 * n, 1);
    for (int i = 1; i <= log2_[3 * n]; i++)
        for (int j = 1; j <= 3 * n; j++)
        {
            int posl = lrmq.query(lft[i - 1][j], rig[i - 1][j]);
            int posr = rrmq.query(lft[i - 1][j], rig[i - 1][j]);
            lft[i][j] = min(lft[i - 1][posl], lft[i - 1][posr]);
            rig[i][j] = max(rig[i - 1][posl], rig[i - 1][posr]);
        }
    for (int j = n + 1; j <= (n << 1); j++)
    {
        int wl = j, wr = j, ans = 0;
        for (int i = log2_[3 * n]; i >= 0; i--)
        {
            if (max(rig[i][wl], rig[i][wr]) - min(lft[i][wl], lft[i][wr]) + 1 >= n)
                continue;
            int wwl = lrmq.query(lft[i][wl], rig[i][wr]);
            int wwr = rrmq.query(lft[i][wl], rig[i][wr]);
            ans += (1 << i), wl = wwl, wr = wwr;
        }
        ans++;
        printf("%d ", ans);
    }
    puts("");
    return 0;
}