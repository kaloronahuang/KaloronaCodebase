// CF868F.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, MAX_M = 30;

typedef long long ll;

const ll INF = (1LL << 61);

int n, m, ai[MAX_N], cnt[MAX_N];
ll dp[MAX_M][MAX_N];

inline int lowbit(int x) { return x & (-x); }

int curt_lb = 1, curt_rb;
ll curt_ans;

ll calc(int l, int r)
{
    while (l < curt_lb)
        curt_ans += cnt[ai[--curt_lb]], cnt[ai[curt_lb]]++;
    while (curt_rb < r)
        curt_ans += cnt[ai[++curt_rb]], cnt[ai[curt_rb]]++;
    while (curt_lb < l)
        cnt[ai[curt_lb]]--, curt_ans -= cnt[ai[curt_lb++]];
    while (r < curt_rb)
        cnt[ai[curt_rb]]--, curt_ans -= cnt[ai[curt_rb--]];
    return curt_ans;
}

void solve(int rd, int l, int r, int LB, int RB)
{
    int mid = (LB + RB) >> 1, gpt;
    ll tmp = 0;
    dp[rd][mid] = INF;
    for (int i = l; i <= min(r, mid - 1); i++)
    {
        tmp = dp[rd - 1][i] + calc(i + 1, mid);
        if (dp[rd][mid] > tmp)
            dp[rd][mid] = tmp, gpt = i;
    }
    if (LB < mid)
        solve(rd, l, gpt, LB, mid - 1);
    if (mid < RB)
        solve(rd, gpt, r, mid + 1, RB);
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    for (int i = 1; i <= n; i++)
        dp[1][i] = dp[1][i - 1] + cnt[ai[i]], cnt[ai[i]]++;
    memset(cnt, 0, sizeof(cnt));
    for (int j = 2; j <= m; j++)
        solve(j, j - 1, n, j, n);
    printf("%lld\n", dp[m][n]);
    return 0;
}