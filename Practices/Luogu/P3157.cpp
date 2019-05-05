// P3157.cpp
#include <bits/stdc++.h>
#define mid ((l + r) >> 1)
using namespace std;

const int MAX_N = 100100, MAX_M = 3e7 + 20000;

int poses[MAX_N], roots[MAX_N], sum[MAX_M], lson[MAX_M], rson[MAX_M];
int n, m, tot, queA[MAX_M], queB[MAX_M];

inline int lowbit(int x) { return x & (-x); }

void update(int qx, int &p, int l, int r, int val)
{
    if (p == 0)
        p = ++tot;
    sum[p] += val;
    if (l == r)
        return;
    if (qx <= mid)
        update(qx, lson[p], l, mid, val);
    else
        update(qx, rson[p], mid + 1, r, val);
}

int query(int qx, int l, int r, int mode)
{
    int totA = 0, totB = 0, ans = 0;
    for (int i = l - 1; i >= 1; i -= lowbit(i))
        queA[++totA] = roots[i];
    for (int i = r; i >= 1; i -= lowbit(i))
        queB[++totB] = roots[i];
    l = 1, r = n;
    while (l < r)
        if (qx <= mid)
        {
            if (mode == 0)
            {
                for (int i = 1; i <= totA; i++)
                    ans -= sum[rson[queA[i]]];
                for (int i = 1; i <= totB; i++)
                    ans += sum[rson[queB[i]]];
            }
            for (int i = 1; i <= totA; i++)
                queA[i] = lson[queA[i]];
            for (int i = 1; i <= totB; i++)
                queB[i] = lson[queB[i]];
            r = mid;
        }
        else
        {
            if (mode == 1)
            {
                for (int i = 1; i <= totA; i++)
                    ans -= sum[lson[queA[i]]];
                for (int i = 1; i <= totB; i++)
                    ans += sum[lson[queB[i]]];
            }
            for (int i = 1; i <= totA; i++)
                queA[i] = rson[queA[i]];
            for (int i = 1; i <= totB; i++)
                queB[i] = rson[queB[i]];
            l = mid + 1;
        }
    return ans;
}

int main()
{
    scanf("%d%d", &n, &m);
    long long ans = 0;
    for (int i = 1, tmpx; i <= n; i++)
    {
        scanf("%d", &tmpx), poses[tmpx] = i;
        ans += query(tmpx, 1, i - 1, 0);
        for (int j = i; j <= n; j += lowbit(j))
            update(tmpx, roots[j], 1, n, 1);
    }
    printf("%lld\n", ans);
    for (int i = 1, tmpx; i < m; i++)
    {
        scanf("%d", &tmpx);
        ans -= query(tmpx, 1, poses[tmpx] - 1, 0);
        ans -= query(tmpx, poses[tmpx] + 1, n, 1);
        printf("%lld\n", ans);
        for (int j = poses[tmpx]; j <= n; j += lowbit(j))
            update(tmpx, roots[j], 1, n, -1);
    }
    return 0;
}