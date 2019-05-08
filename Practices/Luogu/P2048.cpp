// P2048.cpp
#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 5e5 + 2000;

int n, k, L, R, arr[MAX_N], sum[MAX_N], st[20][MAX_N];

struct element
{
    int l, r, lower, upper;
    bool operator<(const element &ele) const { return sum[r] - sum[l - 1] < sum[ele.r] - sum[ele.l - 1]; }
};
priority_queue<element> eleq;

int query(int l, int r)
{
    int d = (int)log2(r - l + 1);
    int a = st[d][l], b = st[d][r - (1 << d) + 1];
    if (sum[a] > sum[b])
        return a;
    else
        return b;
}

int main()
{
    scanf("%d%d%d%d", &n, &k, &L, &R);
    for (int i = 1; i <= n; i++)
        scanf("%d", &arr[i]), sum[i] = sum[i - 1] + arr[i], st[0][i] = i;
    for (int i = 1; i < 20; i++)
        for (int j = 1; j <= n; j++)
            if (sum[st[i - 1][j]] > sum[st[i - 1][j + (1 << (i - 1))]])
                st[i][j] = st[i - 1][j];
            else
                st[i][j] = st[i - 1][j + (1 << (i - 1))];
    for (int i = 1; i <= n - L + 1; i++)
        eleq.push(element{i, query(i + L - 1, min(i + R - 1, n)), i + L - 1, min(i + R - 1, n)});
    long long ans = 0;
    while (k--)
    {
        element e = eleq.top();
        eleq.pop();
        ans += sum[e.r] - sum[e.l - 1];
        if (e.r != e.lower)
            eleq.push(element{e.l, query(e.lower, e.r - 1), e.lower, e.r - 1});
        if (e.r != e.upper)
            eleq.push(element{e.l, query(e.r + 1, e.upper), e.r + 1, e.upper});
    }
    printf("%lld", ans);
    return 0;
}