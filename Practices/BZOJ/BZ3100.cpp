// BZ3100.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1001000;

int n, ai[MAX_N], last[MAX_N], q[MAX_N], head, tail, lft, ans;

void check(int l, int r, int mx_pos)
{
    if (mx_pos > r)
        return;
    if (r - l + 1 == ai[mx_pos])
        ans = max(r - l + 1, ans);
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    head = 1, tail = 0;
    for (int i = 1; i <= n; i++)
    {
        lft = max(lft, last[ai[i]] + 1);
        while (head <= tail && q[head] <= last[ai[i]])
            check(q[head] + 1, i - 1, q[head + 1]), head++;
        last[ai[i]] = i;
        while (head <= tail && ai[q[tail]] <= ai[i])
            check(max(lft, q[tail - 1] + 1), i - 1, q[tail]), tail--;
        q[++tail] = i, q[tail + 1] = 1e9, check(lft, i, q[head]);
    }
    while (head + 1 <= tail)
        check(q[head] + 1, n, q[head + 1]), head++;
    printf("%d\n", ans);
    return 0;
}