// P5899.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e5 + 200, mod = 1e9, INF = 0x3f3f3f3f;

int n, ai[MAX_N];
int tmp_min[MAX_N], tmp_min_sum[MAX_N], tmp_min_sum_id[MAX_N];
int tmp_max[MAX_N], tmp_max_sum[MAX_N], tmp_max_sum_id[MAX_N];
int tmp_c_sum[MAX_N], tmp_c_sum_id[MAX_N];

int calc(int l, int r) { return ((1LL * (l + r) * (r - l + 1)) / 2) % mod; }

int solve(int l, int r)
{
    if (l == r)
        return 1LL * ai[l] * ai[l] % mod;
    int mid = (l + r) >> 1, ret = (0LL + solve(l, mid) + solve(mid + 1, r)) % mod;

    // preprocess;
    tmp_min[mid] = INF, tmp_max[mid] = -INF;
    tmp_min_sum[mid] = tmp_min_sum_id[mid] = tmp_max_sum[mid] = tmp_max_sum_id[mid] = tmp_c_sum[mid] = tmp_c_sum_id[mid] = 0;
    for (int i = mid + 1; i <= r; i++)
    {
        tmp_min[i] = min(tmp_min[i - 1], ai[i]);
        tmp_min_sum[i] = (0LL + tmp_min_sum[i - 1] + tmp_min[i]) % mod;
        tmp_min_sum_id[i] = (0LL + tmp_min_sum_id[i - 1] + 1LL * tmp_min[i] * i % mod) % mod;

        tmp_max[i] = max(tmp_max[i - 1], ai[i]);
        tmp_max_sum[i] = (0LL + tmp_max_sum[i - 1] + tmp_max[i]) % mod;
        tmp_max_sum_id[i] = (0LL + tmp_max_sum_id[i - 1] + 1LL * tmp_max[i] * i % mod) % mod;

        tmp_c_sum[i] = (0LL + tmp_c_sum[i - 1] + 1LL * tmp_min[i] * tmp_max[i] % mod) % mod;
        tmp_c_sum_id[i] = (0LL + tmp_c_sum_id[i - 1] + 1LL * tmp_min[i] * tmp_max[i] % mod * i % mod) % mod;
    }

    int min_ptr = mid, max_ptr = mid, suf_min = INF, suf_max = -INF;
    for (int lptr = mid, pre_min = ai[lptr], pre_max = ai[lptr]; lptr >= l; lptr--)
    {
        pre_min = min(pre_min, ai[lptr]), pre_max = max(pre_max, ai[lptr]);
        while (min_ptr < r && min(suf_min, ai[min_ptr + 1]) >= pre_min)
            min_ptr++, suf_min = min(suf_min, ai[min_ptr]);
        while (max_ptr < r && max(suf_max, ai[max_ptr + 1]) <= pre_max)
            max_ptr++, suf_max = max(suf_max, ai[max_ptr]);

        // the first part:
        int ptr = min(min_ptr, max_ptr);
        ret = (0LL + ret + 1LL * calc(mid + 1 - lptr + 1, ptr - lptr + 1) * pre_min % mod * pre_max % mod) % mod;
        // the second part:
        // it should be seperated;
        if (min_ptr <= max_ptr)
            // max_val is seattled : pre_max;
            // but the min_val isn't certain, we could preprocess it;
            ret = (0LL + ret + (1LL * pre_max * ((0LL + tmp_min_sum_id[max_ptr] + mod - tmp_min_sum_id[min_ptr]) % mod) % mod + mod - 1LL * (lptr - 1) * pre_max % mod * ((0LL + tmp_min_sum[max_ptr] + mod - tmp_min_sum[min_ptr]) % mod) % mod) % mod) % mod;
        else
            // min_val is settled : pre_min;
            // but the max_val isn't certain, we could preprocess it;
            ret = (0LL + ret + (1LL * pre_min * ((0LL + tmp_max_sum_id[min_ptr] + mod - tmp_max_sum_id[max_ptr]) % mod) % mod + mod - 1LL * (lptr - 1) * pre_min % mod * ((0LL + tmp_max_sum[min_ptr] + mod - tmp_max_sum[max_ptr]) % mod) % mod) % mod) % mod;
        // the third part;
        int max_bound = max(min_ptr, max_ptr);
        ret = (0LL + ret + (0LL + tmp_c_sum_id[r] + mod - tmp_c_sum_id[max_bound]) % mod + mod - 1LL * (lptr - 1) * ((0LL + tmp_c_sum[r] + mod - tmp_c_sum[max_bound]) % mod)) % mod;
    }
    return ret;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    printf("%d\n", solve(1, n));
    return 0;
}