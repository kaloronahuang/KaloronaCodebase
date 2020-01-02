// CF1240D.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 3e5 + 200;

int q, n, ai[MAX_N], nxt[MAX_N], dp[MAX_N];
map<int, int> nxt_map[MAX_N];
ll ans;

int main()
{
    scanf("%d", &q);
    while (q--)
    {
        scanf("%d", &n), ans = 0;
        for (int i = 1; i <= n; i++)
            scanf("%d", &ai[i]);
        for (int i = 1; i <= n + 2; i++)
            nxt[i] = -1, dp[i] = 0, nxt_map[i].clear();
        for (int i = n; i >= 1; i--)
        {
            if (nxt_map[i + 1].count(ai[i]))
            {
                int pos = nxt_map[i + 1][ai[i]];
                if (pos <= n && ai[i] == ai[pos])
                {
                    nxt[i] = pos, swap(nxt_map[i], nxt_map[pos + 1]);
                    if (pos <= n - 1)
                        nxt_map[i][ai[pos + 1]] = pos + 1;
                }
            }
            nxt_map[i][ai[i]] = i;
        }
        for (int i = n; i >= 1; i--)
            if (nxt[i] != -1)
                dp[i] = 1 + dp[nxt[i] + 1], ans += dp[i];
        printf("%lld\n", ans);
    }
    return 0;
}