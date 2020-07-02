// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

int n, ai[MAX_N], fac[MAX_N];
char str[MAX_N];

int binomial(int n_, int k_) { return fac[n_] - fac[k_] - fac[n_ - k_]; }

int main()
{
    scanf("%d%s", &n, str + 1);
    bool flag = false;
    for (int i = 1; i <= n; i++)
        ai[i] = str[i] - '1', flag |= (ai[i] == 1);
    for (int i = 1; i <= n; i++)
    {
        int acc = i;
        while (!(acc & 1))
            fac[i]++, acc >>= 1;
        fac[i] += fac[i - 1];
    }
    if (!flag)
        for (int i = 1; i <= n; i++)
            ai[i] >>= 1;
    int ans = 0;
    for (int i = 1; i <= n; i++)
        if ((ai[i] & 1) && (!binomial(n - 1, i - 1)))
            ans ^= 1;
    if (!flag)
        ans <<= 1;
    printf("%d\n", ans);
    return 0;
}