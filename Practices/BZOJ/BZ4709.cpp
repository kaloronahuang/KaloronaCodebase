// BZ4709.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

typedef long long ll;

int n, ai[MAX_N], idx[MAX_N], cnt[MAX_N];
ll dp[MAX_N];
deque<int> stk[MAX_N];

ll calc(int x, ll y) { return dp[x - 1] + 1LL * ai[x] * y * y; }

int check(int x, int y)
{
    int l = 1, r = n, res = n + 1;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (calc(x, mid - idx[x] + 1) >= calc(y, mid - idx[y] + 1))
            r = mid - 1, res = mid;
        else
            l = mid + 1;
    }
    return res;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1, x; i <= n; i++)
    {
        scanf("%d", &ai[i]), x = ai[i];
        idx[i] = ++cnt[ai[i]];
        while (stk[x].size() >= 2 && check(stk[x][stk[x].size() - 2], stk[x].back()) <= check(stk[x].back(), i))
            stk[x].pop_back();
        stk[x].push_back(i);
        while (stk[x].size() >= 2 && check(stk[x][stk[x].size() - 2], stk[x].back()) <= idx[i])
            stk[x].pop_back();
        dp[i] = calc(stk[x].back(), idx[i] - idx[stk[x].back()] + 1);
    }
    printf("%lld\n", dp[n]);
    return 0;
}