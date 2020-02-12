// P4609.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 51000, MAX_B = 210, mod = 1e9 + 7;

int T, n, A, B, S[MAX_N][MAX_B], C[MAX_N][MAX_B];

int main()
{
    S[0][0] = C[0][0] = 1;
    for (int i = 1; i < MAX_N; i++)
    {
        C[i][0] = 1;
        for (int j = 1; j < MAX_B; j++)
            C[i][j] = (0LL + C[i - 1][j - 1] + C[i - 1][j]) % mod, S[i][j] = (0LL + S[i - 1][j - 1] + 1LL * (i - 1) * S[i - 1][j] % mod) % mod;
    }
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d%d", &n, &A, &B);
        if (A == 0 || B == 0 || A + B - 2 > n - 1)
            puts("0");
        else if (n == 1)
            puts("1");
        else
            printf("%lld\n", 1LL * C[A + B - 2][A - 1] % mod * S[n - 1][A + B - 2] % mod);
    }
    return 0;
}