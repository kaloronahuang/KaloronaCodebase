// CF1106F.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
// TODO: Make it fit to the matrix power;
const int MAX_MAT = 150, mod = 998244353;
int n, m, k, ki[MAX_MAT];
struct matrix
{
    ll mat[MAX_MAT][MAX_MAT];
    void basify()
    {
        for (int i = 1; i <= k; i++)
            mat[i][i] = 1;
    }
    ll *operator[](const int &id) { return mat[id]; }
    matrix operator*(const matrix &mt) const
    {
        matrix ans;
        memset(ans.mat, 0, sizeof(ans.mat));
        for (int i = 1; i <= k; i++)
            for (int j = 1; j <= k; j++)
                for (int mid = 1; mid <= k; mid++)
                    ans.mat[i][j] = (ans.mat[i][j] + mat[i][mid] * mt.mat[mid][j] % (mod - 1)) % (mod - 1);
        return ans;
    }
    matrix operator^(const int &tim) const
    {
        matrix ans, bas = *this;
        ans.basify();
        int ti = tim;
        while (ti)
        {
            if (ti & 1)
                ans = ans * bas;
            bas = bas * bas;
            ti >>= 1;
        }
        return ans;
    }
};
ll quick_pow(ll bas, ll tim)
{
    ll ans = 1;
    while (tim)
    {
        if (tim & 1)
            ans = ans * bas % mod;
        bas = bas * bas % mod;
        tim >>= 1;
    }
    return ans;
}
ll bsgs(ll a, ll y)
{
    if (a == 0 && y == 0)
        return 1;
    if (a == 0 && y != 0)
        return -1;
    map<ll, ll> hsh;
    ll u = ceil(sqrt(mod));
    for (int i = 0, x = 1; i <= u; i++, x = x * a % mod)
        hsh[y * x % mod] = i;
    ll unit = quick_pow(a, u);
    for (int i = 1, x = unit; i <= u; i++, x = x * unit % mod)
        if (hsh.count(x))
            return i * u - hsh[x];
    return -1;
}
ll exgcd(ll a, ll b, ll &x, ll &y)
{
    if (b == 0)
    {
        x = 1, y = 0;
        return a;
    }
    ll d = exgcd(b, a % b, x, y), z = x;
    x = y, y = z - (a / b) * y;
    return d;
}
ll gcd(ll a, ll b) { return (b == 0) ? a : gcd(b, a % b); }
ll solve(ll a, ll b, ll c)
{
    if (b == 0)
        return 0;
    ll d = gcd(a, b);
    a /= d, b /= d;
    if (gcd(a, c) != 1)
        return -1;
    ll res, tmp;
    exgcd(a, c, res, tmp);
    res = res * b % c;
    res = (res + c) % c;
    return res;
}
int main()
{
    scanf("%d", &k);
    for (int i = 1; i <= k; i++)
        scanf("%d", &ki[i]);
    scanf("%d%d", &n, &m);
    matrix B;
    for (int i = 1; i <= k; i++)
        B[1][i] = ki[i];
    for (int i = 2; i <= k; i++)
        B[i][i - 1] = 1;
    B = B ^ (n - k);
    ll res = B[1][1], s = bsgs(3, m), ans = solve(res, s, mod - 1);
    if (ans == -1)
        puts("-1");
    else
        printf("%lld", quick_pow(3, ans));
    return 0;
}