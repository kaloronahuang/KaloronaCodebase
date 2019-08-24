// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 20, mod = 1e9 + 7;

int n, k, dp_suffix[MAX_N], dp_prefix[MAX_N], seq[MAX_N];

int main()
{
    scanf("%d%d", &n, &k);

    for (int i = 1; i <= n; i++)
        scanf("%d", &seq[i]);
    long long answer = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = i + 1; j <= n; j++)
            if (seq[i] > seq[j])
                dp_suffix[i]++;
        for (int j = 1; j < i; j++)
            if (seq[i] > seq[j])
                dp_prefix[i]++;
        int coe = ((1LL * k * (k + 1)) >> 1) % mod;
        answer = (answer + 1LL * coe * dp_suffix[i] % mod + 1LL * (coe - k + mod) % mod * dp_prefix[i] % mod) % mod;
    }
    printf("%lld", answer);
    return 0;
}