// LOJ2483.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

typedef long long ll;

int n, q[MAX_N], id[MAX_N];
ll pre[MAX_N], dp[MAX_N], X[MAX_N], Y[MAX_N], hi[MAX_N], wi[MAX_N];

ll pow2(ll x) { return x * x; }

double slope(int i, int j)
{
    if (X[i] == X[j])
        return 1e50 * (Y[j] - Y[i]);
    return (double)(Y[j] - Y[i]) / (X[j] - X[i]);
}

bool compare(int a, int b) { return hi[a] < hi[b]; }

void solve(int l, int r)
{
    if (l == r)
        return (void)(Y[l] += dp[l]);
    int mid = (l + r) >> 1;
    solve(l, mid);
    for (int i = l; i <= r; i++)
        id[i] = i;
    sort(id + l, id + 1 + r, compare);
    int head = 1, tail = 0;
    for (int i = l; i <= r; i++)
        if (id[i] <= mid)
        {
            while (head < tail && slope(q[tail - 1], q[tail]) >= slope(q[tail], id[i]))
                tail--;
            q[++tail] = id[i];
        }
    for (int i = l; i <= r; i++)
        if (id[i] > mid)
        {
            while (head < tail && slope(q[head], q[head + 1]) <= 2LL * hi[id[i]])
                head++;
            dp[id[i]] = min(dp[id[i]], dp[q[head]] + pow2(hi[id[i]] - hi[q[head]]) + pre[id[i] - 1] - pre[q[head]]);
        }
    solve(mid + 1, r);
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &hi[i]);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &wi[i]), pre[i] = pre[i - 1] + wi[i];
    for (int i = 1; i <= n; i++)
        id[i] = i, X[i] = hi[i], Y[i] = pow2(hi[i]) - pre[i];
    memset(dp, 0x7f, sizeof(dp));
    dp[1] = 0, solve(1, n), printf("%lld\n", dp[n]);
    return 0;
}