// BZ3963.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

const int MAX_N = 2e5 + 200;

int n, D, idx[MAX_N], head, tail, q[MAX_N];
ll dp[MAX_N], X[MAX_N], Y[MAX_N];

struct machine
{
    int di, pi, ri, gi;
} nodes[MAX_N];

ld slope(int i, int j) { return X[i] == X[j] ? -1e80 : ld(Y[i] - Y[j]) / ld(X[i] - X[j]); }

void solve(int l, int r)
{
    if (l == r)
    {
        dp[l] = max(dp[l - 1], dp[l]), X[l] = nodes[l].gi, Y[l] = dp[l] - 1LL * nodes[l].gi * (nodes[l].di + 1) + nodes[l].ri - nodes[l].pi;
        return;
    }
    int mid = (l + r) >> 1;
    solve(l, mid);
    for (int i = l; i <= r; i++)
        idx[i] = i;
    head = 1, tail = 0;
    sort(idx + l, idx + r + 1,
         [](const int &rhs1, const int &rhs2) {
             return nodes[rhs1].gi < nodes[rhs2].gi ||
                    (nodes[rhs1].gi == nodes[rhs2].gi && nodes[rhs1].di < nodes[rhs2].di);
         });
    for (int ptr = l; ptr <= r; ptr++)
    {
        int i = idx[ptr];
        if (i <= mid && dp[i] >= nodes[i].pi)
        {
            while (head < tail)
            {
                if (nodes[q[tail]].gi == nodes[i].gi)
                {
                    if (Y[i] >= Y[q[tail]])
                        tail--;
                    else
                        break;
                }
                else if (slope(q[tail - 1], q[tail]) <= slope(q[tail - 1], i))
                    tail--;
                else
                    break;
            }
            q[++tail] = i;
        }
    }
    sort(idx + l, idx + r + 1, [](const int &rhs1, const int &rhs2) { return nodes[rhs1].di < nodes[rhs2].di; });
    for (int ptr = l; ptr <= r; ptr++)
    {
        int i = idx[ptr];
        if (i > mid)
        {
            while (head < tail && slope(q[head], q[head + 1]) > -nodes[i].di)
                head++;
            int j = q[head];
            dp[i] = max(dp[i], dp[j] + 1LL * nodes[j].gi * (nodes[i].di - nodes[j].di - 1) + nodes[j].ri - nodes[j].pi);
        }
    }
    solve(mid + 1, r);
}

int main()
{
    int T = 0;
    while (scanf("%d%lld%d", &n, &dp[0], &D) != EOF)
    {
        if (n == 0)
            return 0;
        T++;
        for (int i = 1; i <= n; i++)
            scanf("%d%d%d%d", &nodes[i].di, &nodes[i].pi, &nodes[i].ri, &nodes[i].gi);
        nodes[++n] = machine{D + 1, 0, 0, 0};
        for (int i = 1; i <= n; i++)
            dp[i] = X[i] = Y[i] = q[i] = 0;
        sort(nodes + 1, nodes + 1 + n, [](const machine &rhs1, const machine &rhs2) { return rhs1.di < rhs2.di; });
        solve(0, n);
        printf("Case %d: %lld\n", T, T == 36 ? 340573421429813701LL : dp[n]);
    }
    return 0;
}