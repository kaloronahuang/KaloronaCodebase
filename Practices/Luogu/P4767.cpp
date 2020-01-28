// P4767.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3300;
typedef long long ll;

int n, m, di[MAX_N], pre[MAX_N], placeTot[MAX_N], place[MAX_N], coeff;
ll dp[MAX_N];

struct tup
{
    int l, r, pt;
} tups[MAX_N << 1];

int calc(int l, int r)
{
    if (l >= r)
        return 0;
    int mid = (l + r) >> 1;
    return (pre[r] - pre[mid] - (r - mid) * di[mid]) + (di[mid] * (mid - l + 1) - (pre[mid] - ((l == 0) ? 0 : pre[l - 1])));
}

ll getDP(int i, int j) { return dp[i] + calc(i + 1, j) + coeff; }

int binaryFind(tup interval, int x)
{
    int l = interval.l, r = interval.r;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (getDP(interval.pt, mid) > getDP(x, mid))
            r = mid - 1;
        else
            l = mid + 1;
    }
    return l;
}

int check(int extra)
{
    int head = 1, tail = 0;
    coeff = extra, tups[++tail] = tup{1, n, 0};
    for (int i = 1; i <= n; i++)
    {
        dp[i] = getDP(tups[head].pt, i), place[i] = tups[head].pt;
        placeTot[i] = placeTot[tups[head].pt] + 1;
        int last_bound = -1;
        while (head <= tail)
            // whole interval is meaningless;
            if (getDP(i, tups[tail].l) < getDP(tups[tail].pt, tups[tail].l))
                last_bound = tups[tail].l, tail--;
            else
            {
                // find the middle point to split the interval into two;
                int pt = binaryFind(tups[tail], i);
                if (pt <= tups[tail].r)
                    last_bound = pt, tups[tail].r = pt - 1;
                break;
            }
        // insert a new one;
        if (last_bound != -1)
            tups[++tail] = tup{last_bound, n, i};
        if (head <= tail)
        {
            // pop the front;
            tups[head].l++;
            if (tups[head].l > tups[head].r)
                head++;
        }
    }
    return placeTot[n];
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &di[i]);
    sort(di + 1, di + 1 + n);
    for (int i = 1; i <= n; i++)
        pre[i] = di[i] + pre[i - 1];
    int l = 0, r = 1e6, res = 0;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (check(mid) <= m)
            r = mid - 1, res = mid;
        else
            l = mid + 1;
    }
    check(res);
    printf("%lld\n", dp[n] - 1LL * res * m);
    return 0;
}