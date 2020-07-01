// CF666C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, mod = 1e9 + 7;

typedef pair<int, int> pii;

int T, n, s, ansBox[MAX_N], pow25[MAX_N], pow26[MAX_N], inv25[MAX_N], inv26[MAX_N];
int fac[MAX_N], fac_inv[MAX_N], qtot;
char str[MAX_N];
vector<pii> requests[MAX_N];

int fpow(int bas, int tim)
{
    int ret = 1;
    while (tim)
    {
        if (tim & 1)
            ret = 1LL * ret * bas % mod;
        bas = 1LL * bas * bas % mod;
        tim >>= 1;
    }
    return ret;
}

int binomial(int n_, int k_) { return 1LL * fac[n_] * fac_inv[n_ - k_] % mod * fac_inv[k_] % mod; }

int main()
{
    scanf("%d%s", &T, str + 1), s = strlen(str + 1);

    pow25[0] = pow26[0] = inv25[0] = inv26[0] = fac[0] = fac_inv[0] = fac_inv[1] = 1;
    for (int i = 1; i < MAX_N; i++)
        pow25[i] = 25LL * pow25[i - 1] % mod, pow26[i] = 26LL * pow26[i - 1] % mod;
    inv25[1] = fpow(25, mod - 2), inv26[1] = fpow(26, mod - 2);
    for (int i = 2; i < MAX_N; i++)
        inv25[i] = 1LL * inv25[1] * inv25[i - 1] % mod, inv26[i] = 1LL * inv26[1] * inv26[i - 1] % mod;
    for (int i = 1; i < MAX_N; i++)
        fac[i] = 1LL * i * fac[i - 1] % mod;
    for (int i = 2; i < MAX_N; i++)
        fac_inv[i] = 1LL * (mod - mod / i) * fac_inv[mod % i] % mod;
    for (int i = 1; i < MAX_N; i++)
        fac_inv[i] = 1LL * fac_inv[i] * fac_inv[i - 1] % mod;

    for (int i = 1; i <= T; i++)
    {
        int typ;
        scanf("%d", &typ);
        if (typ == 1)
            scanf("%s", str + 1), s = strlen(str + 1);
        else
            scanf("%d", &n), requests[s].push_back(make_pair(n, ++qtot));
    }
    for (int S = 1; S < MAX_N; S++)
        if (!requests[S].empty())
        {
            sort(requests[S].begin(), requests[S].end());
            int last = S, pans = 0;
            for (pii u : requests[S])
            {
                for (; last <= u.first; last++)
                {
                    int i = last;
                    pans = (0LL + pans + 1LL * inv26[i] * pow25[i - S] % mod * binomial(i - 1, S - 1) % mod) % mod;
                }
                ansBox[u.second] = 1LL * pans * pow26[u.first] % mod;
            }
        }
    for (int i = 1; i <= qtot; i++)
        printf("%d\n", ansBox[i]);
    return 0;
}