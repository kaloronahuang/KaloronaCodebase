// ARC101B.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 4e5 + 200;

ll nodes[MAX_N << 1];
int n, ai[MAX_N], upper, diff[MAX_N];

int lowbit(int x) { return x & (-x); }

void update(int x, int d)
{
    for (; x <= upper; x += lowbit(x))
        nodes[x] += d;
}

ll query(int x, ll ret = 0)
{
    for (; x; x -= lowbit(x))
        ret += nodes[x];
    return ret;
}

bool check(int mid)
{
    memset(nodes, 0, sizeof(nodes));
    for (int i = 1; i <= n; i++)
        diff[i] = (ai[i] >= mid ? 1 : -1);
    for (int i = 1; i <= n; i++)
        diff[i] += diff[i - 1];
    ll pans = 0;
    for (int i = 0; i <= n; i++)
    {
        pans += query(diff[i] + MAX_N);
        update(diff[i] + MAX_N, 1);
    }
    return pans >= (1LL * n * (n + 1) / 4);
}

int main()
{
    scanf("%d", &n), upper = MAX_N << 1;
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    int l = 0, r = *max_element(ai + 1, ai + 1 + n), res;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (check(mid))
            l = mid + 1, res = mid;
        else
            r = mid - 1;
    }
    printf("%d\n", res);
    return 0;
}