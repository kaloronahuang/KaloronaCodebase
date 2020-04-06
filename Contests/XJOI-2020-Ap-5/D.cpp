// D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, mod = 998244353;

int n, hi[MAX_N], fi[MAX_N];

inline int lowbit(int x) { return x & (-x); }

int main()
{
    scanf("%d", &n);
    hi[1] = 1;
    for (int i = 2; i <= n; i++)
        hi[i] = lowbit(i);
    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j += i)
            fi[j] = (0LL + fi[j] + hi[i]) % mod;
    int ans = 0;
    for (int i = 1; i <= n; i++)
        ans = (0LL + ans + fi[i]) % mod;
    printf("%d\n", ans);
    return 0;
}