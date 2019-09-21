// range.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e7 + 200;

int n, k, p, A, B, C, D, seq[MAX_N], prefix[MAX_N], suffix[MAX_N];

int main()
{
    /*
    freopen("range.in", "r", stdin);
    freopen("range.out", "w", stdout);
    */
    scanf("%d%d%d", &n, &k, &p);
    scanf("%d%d%d%d", &A, &B, &C, &D);
    seq[1] = A;
    for (int i = 2; i <= n; i++)
        seq[i] = (1LL * seq[i - 1] * B + C) % D;
    suffix[0] = prefix[0] = 1;
    for (int block_l = 1; block_l <= n; block_l += k)
    {
        prefix[block_l] = seq[block_l], suffix[min(n, block_l + k - 1)] = seq[min(n, block_l + k - 1)];
        for (int i = block_l + 1; i <= min(n, block_l + k - 1); i++)
            prefix[i] = 1LL * prefix[i - 1] * seq[i] % p;
        for (int i = min(n, block_l + k - 1) - 1; i >= block_l; i--)
            suffix[i] = 1LL * suffix[i + 1] * seq[i] % p;
    }
    int ans = 0;
    for (int i = k; i <= n; i++)
    {
        int pans = 1LL * prefix[i] * suffix[i - k + 1] % p;
        ans ^= pans;
    }
    printf("%d", ans);
    return 0;
}