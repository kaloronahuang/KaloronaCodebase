// BZ1052.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e4 + 200;

int n, xi[MAX_N], yi[MAX_N], upper, lower, lft, rig;
bool occupied[MAX_N];

void init()
{
    upper = lft = 0x3f3f3f3f, rig = lower = 0;
    for (int i = 1; i <= n; i++)
        if (!occupied[i])
            upper = min(upper, xi[i]), lower = max(lower, xi[i]), lft = min(lft, yi[i]), rig = max(rig, yi[i]);
}

bool check(int rect_len, int cnt)
{
    init();
    int cupper = upper, clower = lower, clft = lft, crig = rig;
    bool cvis[MAX_N];
    if (cnt == 1)
        return rect_len >= max(lower - upper, rig - lft);
    for (int i = 1; i <= n; i++)
        cvis[i] = occupied[i];

    for (int i = 1; i <= n; i++)
        if (!occupied[i] && clft <= yi[i] && yi[i] <= clft + rect_len && cupper <= xi[i] && xi[i] <= cupper + rect_len)
            occupied[i] = true;
    if (check(rect_len, cnt - 1))
        return true;
    for (int i = 1; i <= n; i++)
        occupied[i] = cvis[i];

    for (int i = 1; i <= n; i++)
        if (!occupied[i] && clft <= yi[i] && yi[i] <= clft + rect_len && clower - rect_len <= xi[i] && xi[i] <= clower)
            occupied[i] = true;
    if (check(rect_len, cnt - 1))
        return true;
    for (int i = 1; i <= n; i++)
        occupied[i] = cvis[i];

    for (int i = 1; i <= n; i++)
        if (!occupied[i] && crig - rect_len <= yi[i] && yi[i] <= crig && cupper <= xi[i] && xi[i] <= cupper + rect_len)
            occupied[i] = true;
    if (check(rect_len, cnt - 1))
        return true;
    for (int i = 1; i <= n; i++)
        occupied[i] = cvis[i];

    for (int i = 1; i <= n; i++)
        if (!occupied[i] && crig - rect_len <= yi[i] && yi[i] <= crig && clower - rect_len <= xi[i] && xi[i] <= clower)
            occupied[i] = true;
    if (check(rect_len, cnt - 1))
        return true;
    for (int i = 1; i <= n; i++)
        occupied[i] = cvis[i];

    return false;
}

int main()
{
    scanf("%d", &n), upper = lft = 0x3f3f3f3f;
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &xi[i], &yi[i]);
    init();
    int l = 0, r = max(lower - upper, rig - lft), res = 0;
    while (l <= r)
    {
        memset(occupied, false, sizeof(occupied));
        int mid = (l + r) >> 1;
        if (check(mid, 3))
            r = mid - 1, res = mid;
        else
            l = mid + 1;
    }
    printf("%d\n", res);
    return 0;
}