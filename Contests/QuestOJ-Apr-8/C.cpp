// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, mod = 1e9 + 7;

int n, a, b, xi[MAX_N], pow2[MAX_N], cnt[4];

int main()
{
    scanf("%d%d%d", &n, &a, &b), pow2[0] = 1;
    for (int i = 1; i <= n; i++)
        scanf("%d", &xi[i]), pow2[i] = (pow2[i - 1] << 1) % mod, xi[i] %= (a + b);
    bool swapped = false;
    if (a > b)
        swapped = true, swap(a, b);
    int ans_a = 0, ans_b = 0, ans_first = 0, ans_second = 0;
    for (int i = 1; i <= n; i++)
        if (xi[i] < a)
            cnt[0]++;
        else if (xi[i] >= a && xi[i] < b)
            cnt[1]++;
        else if (xi[i] >= b && xi[i] < (a << 1))
            cnt[2]++;
        else
            cnt[3]++;
    ans_a = (0LL + pow2[n] + mod - pow2[n - cnt[1]] + 1LL * pow2[cnt[0] + cnt[2]] * (pow2[cnt[3]] + mod - cnt[3] - 1) % mod) % mod;
    ans_first = 1LL * cnt[3] * pow2[cnt[0] + max(0, cnt[2] - 1)] % mod;
    if (cnt[2])
    {
        ans_a = (0LL + ans_a + 1LL * pow2[cnt[0] + cnt[2] - 1] * cnt[3] % mod) % mod;
        ans_first = (0LL + ans_first + pow2[cnt[0] + cnt[2] - 1]) % mod;
    }
    ans_second = pow2[cnt[0] + max(cnt[2] - 1, 0)];
    if (swapped)
        swap(ans_a, ans_b);
    printf("%d %d %d %d\n", ans_a, ans_b, ans_first, ans_second);
    return 0;
}