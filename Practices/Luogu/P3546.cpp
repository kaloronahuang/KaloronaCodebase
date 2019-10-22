// P3546.cpp
#include <bits/stdc++.h>
#define ull unsigned long long

using namespace std;

const int MAX_N = 1e6 + 200;
const ull bit1 = 133, bit2 = 1235, mod1 = 1e9 + 7, mod2 = 1e9 + 9;

int n;
char str[MAX_N];
ull prefix1[MAX_N], prefix2[MAX_N], pw1[MAX_N], pw2[MAX_N];

ull calc(ull *pre, ull *pw, ull mod, int l, int r)
{
    ull tmp = pre[r] - pre[l - 1] * pw[r - l + 1] % mod;
    while (tmp < 0)
        tmp += mod;
    tmp %= mod;
    return tmp;
}

bool check(int s, int t, int i, int j) { return calc(prefix1, pw1, mod1, s, t) == calc(prefix1, pw1, mod1, i, j) && calc(prefix2, pw2, mod2, s, t) == calc(prefix2, pw2, mod2, i, j); }

int main()
{
    scanf("%d%s", &n, str + 1);
    pw1[0] = pw2[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        pw1[i] = pw1[i - 1] * bit1 % mod1, pw2[i] = pw2[i - 1] * bit2 % mod2;
        prefix1[i] = (prefix1[i - 1] * bit1 + str[i] - 'a') % mod1;
        prefix2[i] = (prefix2[i - 1] * bit2 + str[i] - 'a') % mod2;
    }
    int sub = n >> 1, pos = 0, ans = 0;
    for (int i = sub; i >= 1; i--, pos = min(pos + 2, sub - i))
        if (check(1, i, n - i + 1, n))
        {
            while (pos && !check(i + 1, i + pos, n - i - pos + 1, n - i))
                pos--;
            ans = max(ans, pos + i);
        }
    printf("%d", ans);
    return 0;
}