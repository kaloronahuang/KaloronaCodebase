// BZ2432.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

typedef long long ll;

ll n, loop, mod, fib[MAX_N << 3], pos[MAX_N], inv[MAX_N], len[MAX_N];
bool vis[MAX_N];

struct matrix
{
    ll mat[4][4];
    void clear() { memset(mat, 0, sizeof(mat)); }
    ll *operator[](const int &idx) { return mat[idx]; }
    matrix operator*(const matrix &node)
    {
        matrix ret;
        ret.clear();
        for (int i = 1; i <= 3; i++)
            for (int j = 1; j <= 3; j++)
                for (int k = 1; k <= 3; k++)
                    ret[i][j] = (1LL * ret[i][j] + 1LL * mat[i][k] * node.mat[k][j] % mod) % mod;
        return ret;
    }
    matrix operator^(const ll &idx)
    {
        ll tim = idx;
        matrix ret, bas = *this;
        ret.clear();
        for (int i = 1; i <= 3; i++)
            ret[i][i] = 1;
        for (; tim; tim >>= 1, bas = bas * bas)
            if (tim & 1)
                ret = ret * bas;
        return ret;
    }
} A, B, C, trans[MAX_N];

ll exgcd(ll a, ll b, ll &x, ll &y)
{
    if (b == 0)
    {
        x = 1, y = 0;
        return a;
    }
    ll d = exgcd(b, a % b, x, y), tmp = y;
    y = x - (a / b) * y, x = tmp;
    return d;
}

int main()
{
    scanf("%lld%lld%lld", &n, &loop, &mod), fib[1] = fib[2] = 1;
    for (ll i = 3;; i++)
    {
        fib[i] = (0LL + fib[i - 1] + fib[i - 2]) % loop;
        if (pos[fib[i]] == 0)
            pos[fib[i]] = i;
        if (fib[i] == 1 && fib[i - 1] == 1)
            break;
    }
    A[1][2] = A[2][1] = A[2][2] = A[3][3] = 1;
    B[1][1] = B[2][2] = B[3][3] = 1, B[3][2] = mod - 1;
    C[1][1] = C[1][3] = 1;
    bool flag = false;
    for (ll idx = 1; n;)
    {
        if (inv[idx] == 0)
        {
            ll x, y, d = exgcd(idx, loop, x, y);
            if (d == 1)
                inv[idx] = (x % loop + loop) % loop; //1
            else
                inv[idx] = -1;
        }
        if (inv[idx] == -1)
        {
            C = C * (A ^ n);
            break;
        }
        if (!vis[idx] || flag)
        {
            vis[idx] = true;
            if (pos[inv[idx]] == 0)
            {
                C = C * (A ^ n);
                break;
            }
            len[idx] = pos[inv[idx]];
            if (n >= len[idx])
            {
                //2
                n -= len[idx];
                trans[idx] = (A ^ len[idx]) * B;
                C = C * trans[idx];
                idx = idx * fib[len[idx] - 1] % loop;
            }
            else
            {
                C = C * (A ^ n);
                break;
            }
        }
        else
        {
            matrix D;
            D.clear(), D[1][1] = D[2][2] = D[3][3] = 1;
            ll cnt = 0;
            for (ll i = idx * fib[len[idx] - 1] % loop; i != idx; i = i * fib[len[i] - 1] % loop)
                D = D * trans[i], cnt += len[i];
            D = trans[idx] * D, cnt += len[idx];
            C = C * (D ^ ll(n / cnt));
            n %= cnt, flag = true;
        }
    }
    printf("%lld\n", C[1][2]);
    return 0;
}