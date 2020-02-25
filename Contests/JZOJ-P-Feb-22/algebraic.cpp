// algebraic.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

typedef long long ll;

int n, m;
ll ai[MAX_N], ans;

void fileIO()
{
    freopen("algebraic.in", "r", stdin);
    freopen("algebraic.out", "w", stdout);
}

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }

int main()
{
    // fileIO();
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &ai[i]);
    scanf("%d", &m), sort(ai + 1, ai + 1 + n), reverse(ai + 1, ai + n + 1);
    while (m--)
    {
        int k;
        scanf("%d", &k), ans = 0;
        if (k == 0)
        {
            for (int i = 1; i <= n; i++)
                ans += 1LL * ai[i] * ai[i];
            printf("%lld\n", ans);
            continue;
        }
        int loop_num = gcd(n, k), loop_len = n / loop_num;
        for (int start_pos = 0; start_pos < n; start_pos += loop_len)
        {
            ans += 1LL * ai[start_pos + 1] * ai[start_pos + 2] + 1LL * ai[start_pos + loop_len - 1] * ai[start_pos + loop_len];
            for (int i = 1; i <= loop_len - 2; i++)
                ans += 1LL * ai[start_pos + i] * ai[start_pos + i + 2];
        }
        printf("%lld\n", ans);
    }
    return 0;
}