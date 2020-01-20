// station.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;
typedef long long ll;

int n, k, place[MAX_N], q[MAX_N], choice[MAX_N];
ll ai[MAX_N], pre[MAX_N], dp[MAX_N];

ll calc(int l, int r)
{
    int mid = (l + r + 1) >> 1;
    return pre[r] + pre[l] - pre[mid] - pre[mid - 1] - (((r - l + 1) & 1) * ai[mid]);
}

bool compare(int i, int j, int k) { return dp[i] + calc(i, k) < dp[j] + calc(j, k) || (dp[i] + calc(i, k) == dp[j] + calc(j, k) && place[i] < place[j]); }

int solve(ll coeff)
{
    memset(dp, 0x3f, sizeof(dp)), memset(place, 0, sizeof(place));
    int head = 1, tail = 1;
    q[1] = dp[0] = 0, choice[1] = 1;
    for (int i = 1; i <= n; i++)
    {
        while (head < tail && choice[head + 1] <= i)
            head++;
        dp[i] = dp[q[head]] + calc(q[head], i) + coeff, place[i] = place[q[head]] + 1;
        while (head <= tail && compare(i, q[tail], choice[tail]))
            tail--;
        int l = choice[tail], r = n + 1, res;
        while (l < r)
        {
            int mid = (l + r) >> 1;
            if (compare(i, q[tail], mid))
                r = mid;
            else
                l = mid + 1;
        }
        res = l;
        if (res <= n)
            q[++tail] = i, choice[tail] = res;
    }
    return place[n];
}

int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &ai[i]), pre[i] = pre[i - 1] + ai[i];
    ll l = 0, r = pre[n] + 1, offset = 0;
    while (l < r)
    {
        ll mid = (l + r) >> 1;
        if (solve(mid) <= k)
            r = mid;
        else
            l = mid + 1;
    }
    offset = l;
    solve(offset);
    printf("%lld\n", dp[n] - offset * k);
    return 0;
}