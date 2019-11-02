// CF1168A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e5 + 200;

int n, seq[MAX_N], mod, mx[MAX_N], mi[MAX_N];

bool check(int mid)
{
    for (int i = 1, last_val = 0; i <= n; i++)
    {
        int lft = seq[i], rig = seq[i] + mid;
        if ((lft <= last_val && last_val <= rig) || (lft <= last_val + mod && last_val + mod <= rig))
            continue;
        if (lft < last_val)
            return false;
        else
            last_val = lft;
    }
    return true;
}

int main()
{
    scanf("%d%d", &n, &mod);
    for (int i = 1; i <= n; i++)
        scanf("%d", &seq[i]);
    int l = 0, r = mod - 1, ans = 0;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (check(mid))
            r = mid - 1, ans = mid;
        else
            l = mid + 1;
    }
    printf("%d", ans);
    return 0;
}