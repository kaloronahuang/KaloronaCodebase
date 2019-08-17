// B.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 2e5 + 200;

ll n, tail, arr[MAX_N], dp[MAX_N], A, B, C, D, stk_pos[MAX_N], stk_val[MAX_N], ans[MAX_N];

ll calc(ll x) { return A * x * x * x + B * x * x + C * x + D; }

int main()
{
    freopen("min.in", "r", stdin);
    freopen("min.out", "w", stdout);
    scanf("%lld%lld%lld%lld%lld", &n, &A, &B, &C, &D);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &arr[i]);

    dp[0] = 0;

    for (int i = 1; i <= n; i++)
    {
        ll curt_ans = dp[i - 1];
        while (tail > 0 && arr[stk_pos[tail]] >= arr[i])
            curt_ans = max(curt_ans, stk_val[tail]), tail--;
        stk_pos[++tail] = i, stk_val[tail] = curt_ans;
        if (tail > 1)
            ans[tail] = max(curt_ans + calc(arr[i]), ans[tail - 1]);
        else
            ans[tail] = curt_ans + calc(arr[i]);
        dp[i] = ans[tail];
    }
    printf("%lld", dp[n]);
    return 0;
}