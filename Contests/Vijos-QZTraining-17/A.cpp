// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 100100;

int seq[MAX_N], n, k;

bool check(int mid)
{
    int ans = 1, last = 1;
    for (int i = 2; i <= n; i++)
        if (seq[i] - seq[last] >= mid)
            ans++, last = i;
    return ans >= k;
}

int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d", &seq[i]);
    sort(seq + 1, seq + 1 + n);
    int l = 0, r = 1e9, ans = 0;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (check(mid))
            l = mid + 1, ans = mid;
        else
            r = mid - 1;
    }
    printf("%d", ans);
    return 0;
}