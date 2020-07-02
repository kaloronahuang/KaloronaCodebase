// BZ4488.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

typedef long long ll;

int n, log2_[MAX_N];
ll ai[MAX_N], st[20][MAX_N];

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }

ll query(int l, int r)
{
    int d = log2_[r - l + 1];
    return gcd(st[d][l], st[d][r - (1 << d) + 1]);
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &ai[i]), st[0][i] = ai[i];
    for (int i = 2; i <= n; i++)
        log2_[i] = log2_[i >> 1] + 1;
    for (int i = 1; i < 20; i++)
        for (int j = 1; j + (1 << i) - 1 <= n; j++)
            st[i][j] = gcd(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
    ll ans = 0;
    for (int i = 1, last_pos; i <= n; i++)
    {
        vector<int> intervals;
        ll d = ai[i];
        last_pos = i;
        while (last_pos > 0)
        {
            d = gcd(d, ai[last_pos]);
            int l = 1, r = last_pos, res;
            // printf("%d %d\n", l, r);
            while (l <= r)
            {
                int mid = (l + r) >> 1;
                if (query(mid, i) == d)
                    r = mid - 1, res = mid;
                else
                    l = mid + 1;
            }
            intervals.push_back(res), last_pos = res - 1; //, printf("%d %d %d\n", last_pos, res, i);
        }
        d = ai[i];
        for (int x : intervals)
            d = query(x, i), ans = max(ans, 1LL * (i - x + 1) * d);
    }
    printf("%lld\n", ans);
    return 0;
}