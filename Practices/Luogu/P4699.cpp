// P4699.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

int n, ai[MAX_N], seq[MAX_N], dst[MAX_N], dp[MAX_N], mx[MAX_N];

bool compare(int a, int b) { return ai[a] < ai[b]; }

int check(int mid)
{
    for (int i = 1; i <= n; i++)
    {
        int pos = i - dst[i];
        if (pos < 0)
            dp[i] = -1;
        else
            dp[i] = (mx[pos] >= i - mid) ? dp[mx[pos]] + 1 : -1;
        mx[i] = dp[i] >= dp[mx[i - 1]] ? i : mx[i - 1];
    }
    return dp[n];
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]), seq[i] = i;
    sort(seq + 1, seq + 1 + n, compare);
    for (int i = 1; i <= n; i++)
        dst[i] = ai[seq[i]];
    int l = 0, r = n, ans = 0, res = check(n);
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (check(mid) == res)
            r = mid - 1, ans = mid;
        else
            l = mid + 1;
    }
    res = check(ans);
    printf("%d\n", res);
    for (int i = n; i >= 1;)
    {
        int j = mx[i - dst[i]];
        printf("%d ", i - j);
        while (i > j)
            printf("%d ", seq[i--]);
        puts("");
    }
    return 0;
}