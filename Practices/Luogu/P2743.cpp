// P2743.cpp
#include <bits/stdc++.h>
#define ull unsigned long long

using namespace std;

const int MAX_N = 5050, bitnum = 233;

int n, seq[MAX_N], diff[MAX_N];
ull prefix[MAX_N], pow_bit[MAX_N];
map<ull, int> mp;

bool check(int mid)
{
    mp.clear();
    for (int i = 1; i + mid - 1 <= n; i++)
    {
        ull hash_val = prefix[i + mid - 1] - prefix[i] * pow_bit[mid - 1];
        if (mp.count(hash_val))
        {
            if (mp[hash_val] + mid - 1 < i)
                return true;
        }
        else
            mp[hash_val] = i;
    }
    return false;
}

int main()
{
    scanf("%d", &n);
    for (int i = pow_bit[0] = 1; i <= n; i++)
    {
        scanf("%d", &seq[i]), diff[i] = seq[i] - seq[i - 1];
        prefix[i] = prefix[i - 1] * bitnum + (abs(diff[i]) << 1) + (diff[i] < 0), pow_bit[i] = pow_bit[i - 1] * bitnum;
    }
    int l = 5, r = 5050, ans = 0;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (check(mid))
            ans = mid, l = mid + 1;
        else
            r = mid - 1;
    }
    printf("%d", ans);
    return 0;
}