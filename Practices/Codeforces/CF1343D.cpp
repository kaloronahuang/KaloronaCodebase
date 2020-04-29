// CF1343D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int T, n, k, ai[MAX_N], diff[MAX_N << 1];

void mark(int l, int r, int val)
{
    r = min(r, k << 1);
    if (l <= r)
        diff[l] += val, diff[r + 1] -= val;
}

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &n, &k);
        for (int i = 1; i <= n; i++)
            scanf("%d", &ai[i]);
        for (int i = 1, j = n; i <= j; i++, j--)
        {
            // a_i + a_j \in [];
            if (ai[i] > k && ai[j] > k)
                mark(1, k << 1, 2);
            else
            {
                mark(1, min(ai[i], ai[j]), 2);
                mark(min(ai[i], ai[j]) + 1, min(ai[i], k) + min(ai[j], k) - 1, 1);
                mark(min(ai[i], k) + min(ai[j], k) + 1, max(ai[i], ai[j]) + k, 1);
                mark(max(ai[i], ai[j]) + k + 1, k << 1, 2);
            }
        }
        int ans = 0x3f3f3f3f;
        for (int i = 1; i <= (k << 1); i++)
            diff[i] += diff[i - 1], ans = min(ans, diff[i]);
        printf("%d\n", ans);
        for (int i = 1; i <= (k << 1) + 10; i++)
            diff[i] = 0;
    }
    return 0;
}