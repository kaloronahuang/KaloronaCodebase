// hakugai.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 50;

int T, a, b, n, level, mod;

typedef long long ll;

ll loops[MAX_N], tot, cmod;

void fileIO(string src)
{
    freopen((src + ".in").c_str(), "r", stdin);
    freopen((src + ".out").c_str(), "w", stdout);
}

struct matrix
{
    ll mat[2][2];
    ll *operator[](const int &id) { return mat[id]; }
    void clear() { memset(mat, 0, sizeof(mat)); };
    void epsilon() { mat[0][0] = mat[1][1] = 1; }
    matrix operator*(const matrix &rhs)
    {
        matrix ret;
        ret.clear();
        for (int i = 0; i < 2; i++)
            for (int k = 0; k < 2; k++)
                if (mat[i][k])
                    for (int j = 0; j < 2; j++)
                        if (rhs.mat[k][j])
                            ret[i][j] = (0LL + ret[i][j] + 1LL * mat[i][k] * rhs.mat[k][j] % cmod) % cmod;
        return ret;
    }
    matrix operator^(const ll &rhs)
    {
        matrix ret, bas = *this;
        ret.clear(), ret.epsilon();
        ll tim = rhs;
        while (tim)
        {
            if (tim & 1LL)
                ret = ret * bas;
            bas = bas * bas;
            tim >>= 1;
        }
        return ret;
    }
} init, trans;

ll getGn(ll x, ll cm)
{
    cmod = cm;
    if (x == 0)
        return a;
    if (x == 1)
        return b;
    return (1LL * ((init * (trans ^ (2 * x - 1)))[0][1]) * b % cmod + cmod - 1LL * ((init * (trans ^ (2 * (x - 1) - 1)))[0][1]) * a % cmod) % cmod;
}

ll getFn(ll pbase)
{
    if (pbase == 2)
        return 3;
    if (pbase == 3)
        return 8;
    if (pbase == 5)
        return 20;
    if (pbase % 5 == 1 || pbase % 5 == 4)
        return pbase - 1;
    return 2 * pbase + 2;
}

ll getLoopLen(ll x)
{
    tot = 0;
    ll acc = x;
    for (int i = 2; 1LL * i * i <= acc; i++)
        if (acc % i == 0)
        {
            loops[++tot] = getFn(i);
            ll cnt = 1;
            while (acc % i == 0)
                acc /= i, cnt *= i;
            cnt /= i, loops[tot] *= cnt;
        }
    if (acc != 1)
        loops[++tot] = getFn(acc);
    ll loop = loops[1];
    for (int i = 2; i <= tot; i++)
        loop = (loop / __gcd(loop, loops[i])) * loops[i];
    return loop;
}

ll solve(ll n_, ll k_, ll cm)
{
    if (k_ == 0)
        return n_ % cm;
    ll nxt_loop = getLoopLen(cm), now = solve(n_, k_ - 1, nxt_loop);
    ll res = getGn(now, cm);
    return res;
}

int main()
{
    // fileIO("hakugai");
    scanf("%d", &T);
    trans.clear(), trans[1][0] = 1, trans[1][1] = 1, trans[0][1] = 1;
    init.clear(), init[0][0] = 0, init[0][1] = 1;
    while (T--)
    {
        scanf("%d%d%d%d%d", &a, &b, &n, &level, &mod);
        // get loop;
        printf("%lld\n", solve(n, level, mod));
    }
    return 0;
}