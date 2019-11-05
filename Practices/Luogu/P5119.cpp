// P5119.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, m, c, seq[MAX_N];

bool check(int mid)
{
    seq[n + 1] = 2e9 + 200;
    int ret = 0;
    for (int i = 1, last_pos = 0; i <= n; i++)
        if (i - last_pos == c || seq[i + 1] - seq[last_pos + 1] > mid)
            last_pos = i, ret++;
    return ret <= m;
}

int main()
{
    scanf("%d%d%d", &n, &m, &c);
    for (int i = 1; i <= n; i++)
        scanf("%d", &seq[i]);
    sort(seq + 1, seq + 1 + n);
    int l = 0, r = 1e9, ans = 0;
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