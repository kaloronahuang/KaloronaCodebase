// P3477.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e5 + 200;

int n, mod, ai[MAX_N], cnt[MAX_N], fac[MAX_N], upper, pbase[MAX_N], pr[MAX_N], ptot, nodes[MAX_N], powlist[MAX_N];
vector<int> mp;

int ripe(int x) { return lower_bound(mp.begin(), mp.end(), x) - mp.begin() + 1; }

int exgcd(int a, int b, int &x, int &y)
{
    if (b == 0)
    {
        x = 1, y = 0;
        return a;
    }
    int d = exgcd(b, a % b, x, y), tmp = x;
    x = y, y = tmp - (a / b) * y;
    return d;
}

int getInv(int u, int cmod)
{
    int x, y, d = exgcd(u, cmod, x, y);
    return d == 1 ? (x + cmod) % cmod : -1;
}

inline int lowbit(int x) { return x & (-x); }

void update(int x, int d)
{
    for (; x < MAX_N; x += lowbit(x))
        nodes[x] += d;
}

int query(int x, int ret = 0)
{
    for (; x; x -= lowbit(x))
        ret += nodes[x];
    return ret;
}

// pair<int, int> = make_pair(a, b), x = p^a \times b;
pair<int, int> getFactorized(int x, int p)
{
    int a = 0, b = 0;
    while (x % p == 0)
        a++, x /= p;
    b = x;
    return make_pair(a, b);
}

int solve(int pb, int p)
{
    for (int i = powlist[0] = 1; i < MAX_N; i++)
        powlist[i] = 1LL * powlist[i - 1] * pb % p;
    memset(cnt, 0, sizeof(cnt)), memset(nodes, 0, sizeof(nodes));
    int ret = 1, coeff = 1, pbase_idx = 0;
    cnt[ai[n]] = 1, update(ai[n], 1);
    for (int i = n - 1; i >= 1; i--)
    {
        pair<int, int> res = getFactorized(n - i, pb);
        pbase_idx += res.first, coeff = 1LL * coeff * res.second % p;
        res = getFactorized(++cnt[ai[i]], pb);
        pbase_idx -= res.first, coeff = 1LL * coeff * getInv(res.second, p) % p;
        update(ai[i], 1), ret = (0LL + ret + 1LL * coeff * powlist[pbase_idx] % p * query(ai[i] - 1) % p) % p;
    }
    return ret;
}

int main()
{
    scanf("%d%d", &n, &mod);
    for (int i = fac[0] = 1; i <= n; i++)
        scanf("%d", &ai[i]), mp.push_back(ai[i]), fac[i] = 1LL * fac[i - 1] * i % mod;
    int acc = mod;
    for (int i = 2; 1LL * i * i <= acc; i++)
        if (acc % i == 0)
        {
            pbase[++ptot] = i, pr[ptot] = 1;
            while (acc % i == 0)
                acc /= i, pr[ptot] *= i;
        }
    if (acc != 1)
        pbase[++ptot] = acc, pr[ptot] = acc;
    int ans = 0;
    for (int i = 1; i <= ptot; i++)
    {
        int curt = pbase[i], res = solve(curt, pr[i]), M = mod / pr[i];
        ans = (0LL + ans + 1LL * res * M % mod * getInv(M, pr[i])) % mod;
    }
    printf("%d\n", ans);
    return 0;
}