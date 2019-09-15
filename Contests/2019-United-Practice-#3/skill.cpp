// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 10000100;

int prime[MAX_N], tot, n, k;
bool vis[MAX_N], tag[MAX_N];

int main()
{
    freopen("skill.in", "r", stdin);
    freopen("skill.out", "w", stdout);
    scanf("%d%d", &n, &k);
    for (int i = 2; i <= n; i++)
    {
        if (!vis[i])
            prime[++tot] = i;
        for (int j = 1; j <= tot && 1LL * prime[j] * i <= n; j++)
        {
            vis[i * prime[j]] = true;
            if (i % prime[j] == 0)
                break;
        }
    }
    if (k == n - 1)
        printf("%d", tot), exit(0);
    for (int num = 1; num <= tot; num++)
    {
        int U = (1 << num) - 1, ans = 0;
        for (int sub = U; sub; sub = (sub - 1) & U)
        {
            int pans = 1, bit = 0;
            for (int j = 1; j <= tot; j++)
                if (sub & (1 << (j - 1)))
                    bit++, pans *= prime[j];

            int opt = (bit & 1) ? 1 : -1;
            ans += opt * int(n / pans);
        }
        if (ans >= k)
            printf("%d", num), exit(0);
    }
    return 0;
}