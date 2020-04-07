// LOJ3228.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e4 + 200;

int n, k, mod, f[MAX_N], ans[MAX_N];

void mul(int idx)
{
    for (int i = MAX_N - 1; i >= idx; i--)
        f[i] = (0LL + f[i] + mod - f[i - idx]) % mod;
    for (int i = 1; i < MAX_N; i++)
        f[i] = (0LL + f[i] + f[i - 1]) % mod;
}

void div(int idx)
{
    for (int i = MAX_N - 1; i >= 1; i--)
        f[i] = (0LL + f[i] + mod - f[i - 1]) % mod;
    for (int i = idx; i < MAX_N; i++)
        f[i] = (0LL + f[i] + f[i - idx]) % mod;
}

int main()
{
    scanf("%d%d%d", &n, &k, &mod), f[0] = 1;
    for (int i = 1; i <= n; i++)
        mul(i);
    for (int i = 1; i <= n; i++)
        ans[i] = f[k];
    for (int i = 2; i <= n; i++)
    {
        div(i);
        for (int j = 1; j + i - 1 <= n; j++)
        {
            ans[j] = (0LL + ans[j] + ((k - i + 1) >= 0 ? f[k - i + 1] : 0)) % mod;
            ans[j + i - 1] = (0LL + ans[j + i - 1] + f[k]) % mod;
        }
        mul(i);
    }
    for (int i = 1; i <= n; i++)
        printf("%d ", ans[i]);
    puts("");
    return 0;
}