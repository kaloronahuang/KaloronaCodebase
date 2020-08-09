// E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int n, m, ai[MAX_N];

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= 2 * n; i++)
        scanf("%d", &ai[i]);
    sort(ai + 1, ai + 1 + 2 * n);
    int l = 0, r = n, res;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        bool valid = true;
        for (int i = 2 * mid + 1; i <= (n << 1); i++)
            if (ai[i] + ai[2 * n + 2 * mid + 1 - i] < m)
            {
                valid = false;
                break;
            }
        if (valid)
            r = mid - 1, res = mid;
        else
            l = mid + 1;
    }
    int pos = res << 1;
    int ans = 0;
    for (int i = 1; i <= pos; i++)
        ans = max(ans, ai[i] + ai[pos - i + 1]);
    for (int i = pos + 1; i <= (n << 1); i++)
        ans = max(ans, (ai[i] + ai[(n << 1) + pos - i + 1]) % m);
    printf("%lld\n", ans);
    return 0;
}