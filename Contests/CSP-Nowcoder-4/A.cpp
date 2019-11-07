// A.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 1e5 + 200, mod = 1e9 + 7, inv2 = 500000004;

int n, k, arr[MAX_N], tmp[MAX_N], last_pos[MAX_N];
bool first_pos[MAX_N];
map<int, int> mp;

int interval_calc(int len) { return 1LL * len * (len + 1) % mod * inv2 % mod; }

int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d", &arr[i]);
    // discrete;
    int tot = 0;
    for (int i = 1; i <= n; i++)
    {
        if (mp[arr[i]] == 0)
            mp[arr[i]] = ++tot;
        arr[i] = mp[arr[i]];
    }
    int ans = 1LL * interval_calc(1LL * n * k % mod) * tot % mod;
    for (int i = 1; i <= n; i++)
    {
        if (last_pos[arr[i]] == 0)
            first_pos[i] = true;
        else
            // delete the redundent one;
            ans = (1LL * ans - 1LL * interval_calc(i - last_pos[arr[i]] - 1) * k % mod + mod) % mod;
        last_pos[arr[i]] = i;
    }
    for (int i = 1; i <= n; i++)
        if (first_pos[i])
            ans = (1LL * ans - 1LL * interval_calc(i - 1 + n - last_pos[arr[i]]) * (k - 1) % mod + mod - interval_calc(i - 1) + mod - interval_calc(n - last_pos[arr[i]]) + mod) % mod;
    while (ans < 0)
        ans += mod;
    ans %= mod;
    printf("%d", ans);
    return 0;
}