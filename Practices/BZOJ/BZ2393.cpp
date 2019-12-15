// BZ2393.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 1e5 + 200;

ll L, R, numbers[MAX_N], tot, ans;

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }

void dfs(int u, int dep, ll prod)
{
    if (u > tot)
    {
        if (dep & 1)
            ans += (R / prod) - ((L - 1) / prod);
        else if (dep != 0)
            ans -= (R / prod) - ((L - 1) / prod);
    }
    else
    {
        dfs(u + 1, dep, prod);
        ll nprod = prod * numbers[u] / gcd(prod, numbers[u]);
        if (nprod <= R)
            dfs(u + 1, dep + 1, nprod);
    }
}

int main()
{
    ll mx_digit = 0, mx_power = 1;
    scanf("%lld%lld", &L, &R);
    while (mx_power < R)
        mx_digit++, mx_power *= 10LL;
    // generate the 2/9 numbers;
    for (int len = 1; len <= mx_digit; len++)
        for (int stat = 0; stat < (1 << len); stat++)
        {
            ll acc = 0;
            bool flag = true;
            for (int i = len - 1; i >= 0; i--)
                acc = acc * 10LL + ((stat & (1 << i)) ? 9 : 2);
            for (int i = 1; i <= tot; i++)
                if (acc % numbers[i] == 0)
                {
                    flag = false;
                    break;
                }
            if (flag)
                numbers[++tot] = acc;
        }
    dfs(1, 0, 1), printf("%lld\n", ans);
    return 0;
}