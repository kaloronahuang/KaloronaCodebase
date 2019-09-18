// T98534.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 1e7 + 20;

ll seq1[MAX_N], tot1, seq2[MAX_N], tot2, n;

int main()
{
    scanf("%lld", &n);
    for (ll i = 3; i * i <= n; i++)
        if (n % i == 0 && (i & 1) && n / i * (i - 1) != 0)
            // odd;
            seq1[++tot1] = n / i * (i - 1);
    for (ll i = 1; i * i <= n; i++)
        if (n % i == 0 && ((n / i) & 1) && n / (n / i) * ((n / i) - 1) != 0)
            // odd;
            seq2[++tot2] = n / (n / i) * ((n / i) - 1);
    printf("%lld ", tot1 + tot2);
    for (int i = 1; i <= tot1; i++)
        printf("%lld ", seq1[i]);
    for (int i = tot2; i >= 1; i--)
        printf("%lld ", seq2[i]);
    return 0;
}