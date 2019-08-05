// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, arr[MAX_N], pos[MAX_N], q, log2_[MAX_N];
int stmax[18][MAX_N], stmin[18][MAX_N], posmax[18][MAX_N], posmin[18][MAX_N];

inline int query_pos_max(int l, int r)
{
    int len = r - l + 1, k = log2_[len];
    return max(posmax[k][l], posmax[k][l + len - (1 << k)]);
}

inline int query_pos_min(int l, int r)
{
    int len = r - l + 1, k = log2_[len];
    return min(posmin[k][l], posmin[k][l + len - (1 << k)]);
}

inline int query_max(int l, int r)
{
    int len = r - l + 1, k = log2_[len];
    return max(stmax[k][l], stmax[k][l + len - (1 << k)]);
}

inline int query_min(int l, int r)
{
    int len = r - l + 1, k = log2_[len];
    return min(stmin[k][l], stmin[k][l + len - (1 << k)]);
}

int main()
{

    freopen("sequence23.in", "r", stdin);
    freopen("sequence.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 2; i <= n; i++)
        log2_[i] = log2_[i >> 1] + 1;
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &arr[i]), pos[arr[i]] = i;
        stmax[0][i] = arr[i], stmin[0][i] = arr[i];
        posmin[0][arr[i]] = i, posmax[0][arr[i]] = i;
    }
    for (int i = 1; (1 << i) <= n; ++i)
        for (int j = 1; j <= n; ++j)
        {
            stmax[i][j] = max(stmax[i - 1][j], stmax[i - 1][j + (1 << (i - 1))]);
            stmin[i][j] = min(stmin[i - 1][j], stmin[i - 1][j + (1 << (i - 1))]);
            posmax[i][j] = max(posmax[i - 1][j], posmax[i - 1][j + (1 << (i - 1))]);
            posmin[i][j] = min(posmin[i - 1][j], posmin[i - 1][j + (1 << (i - 1))]);
        }
    scanf("%d", &q);
    while (q--)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        int mx, mi;
        while (r - l + 1 != (mx = query_max(l, r)) - (mi = query_min(l, r)) + 1)
        {
            l = min(l, query_pos_min(mi, mx));
            r = max(l, query_pos_max(mi, mx));
        }
        printf("%d %d\n", l, r);
    }
    return 0;
}