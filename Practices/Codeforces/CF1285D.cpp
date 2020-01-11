// CF1285D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, ai[MAX_N], ans = 0x7fffffff, tmp[MAX_N];

void solve(int l, int r, int dep)
{
    if (l > r)
        return;
    if (dep == -1)
    {
        int max_val = 0;
        for (int i = l; i <= r; i++)
            max_val = max(max_val, ai[i]);
        ans = min(ans, max_val);
        return;
    }
    int lptr = l, rptr = r, cnt0 = 0, cnt1 = 0;
    for (int i = l; i <= r; i++)
        if (ai[i] & (1 << dep))
            tmp[rptr--] = ai[i], cnt1++;
        else
            tmp[lptr++] = ai[i], cnt0++;
    if (cnt1 == (r - l + 1))
        for (int i = l; i <= r; i++)
            ai[i] = (tmp[i] ^ (1 << dep));
    else if (cnt0 == (r - l + 1))
        for (int i = l; i <= r; i++)
            ai[i] = tmp[i];
    else
        for (int i = l; i <= r; i++)
            ai[i] = (tmp[i] | (1 << dep));
    solve(l, lptr - 1, dep - 1), solve(lptr, r, dep - 1);
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    solve(1, n, 29);
    printf("%d\n", ans);
    return 0;
}