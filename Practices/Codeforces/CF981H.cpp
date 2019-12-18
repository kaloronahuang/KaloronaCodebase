// CF981H.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const ll MAX_N = 2e5 + 200, mod = 998244353;

int n, k, head[MAX_N], current, siz[MAX_N], fac[MAX_N], fac_inv[MAX_N];
int f[MAX_N], g[MAX_N], dp[MAX_N], gpans;
vector<int> ans[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

int quick_pow(int bas, int tim)
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

const int G = 3, Gi = quick_pow(G, mod - 2);

int poly_bit, poly_siz, rev[MAX_N], ui[MAX_N], vi[MAX_N];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

int getRev(int x, int bit)
{
    int curt = 0;
    for (int i = 0; i < bit; i++)
        curt |= (((x >> i) & 1) << (bit - 1 - i));
    return curt;
}

void ntt(vector<int> &arr, int dft)
{
    for (int i = 0; i < poly_siz; i++)
        if (i < (rev[i] = getRev(i, poly_bit)))
            swap(arr[i], arr[rev[i]]);
    for (int step = 1; step < poly_siz; step <<= 1)
    {
        int omega_n = quick_pow(dft == 1 ? G : Gi, (mod - 1) / (step << 1));
        for (int j = 0; j < poly_siz; j += (step << 1))
        {
            int omega_nk = 1;
            for (int k = j; k < j + step; k++, omega_nk = 1LL * omega_nk * omega_n % mod)
            {
                int t = 1LL * omega_nk * arr[k + step] % mod;
                arr[k + step] = (1LL * arr[k] + mod - t) % mod;
                arr[k] = (1LL * arr[k] + t) % mod;
            }
        }
    }
    if (dft == -1)
    {
        int inv = quick_pow(poly_siz, mod - 2);
        for (int i = 0; i < poly_siz; i++)
            arr[i] = 1LL * arr[i] * inv % mod;
    }
}

vector<int> polyMultiply(vector<int> A, vector<int> B)
{
    int n = A.size(), m = B.size(), len = n + m;
    poly_bit = poly_siz = 0;
    while ((1 << poly_bit) < len)
        poly_bit++;
    poly_siz = (1 << poly_bit);
    while (A.size() < poly_siz)
        A.push_back(0);
    while (B.size() < poly_siz)
        B.push_back(0);
    ntt(A, 1), ntt(B, 1);
    for (int i = 0; i < poly_siz; i++)
        A[i] = 1LL * A[i] * B[i] % mod;
    ntt(A, -1);
    while (!A.empty() && A.back() == 0)
        A.pop_back();
    return A;
}

vector<int> solve(int l, int r, const vector<int> &curt)
{
    if (l == r - 1)
        return vector<int>{1, curt[l]};
    else
    {
        int mid = (l + r) >> 1;
        return polyMultiply(solve(l, mid, curt), solve(mid, r, curt));
    }
}

void fac_init()
{
    for (int i = fac[0] = 1; i <= MAX_N - 1; i++)
        fac[i] = 1LL * fac[i - 1] * i % mod;
    fac_inv[MAX_N - 1] = quick_pow(fac[MAX_N - 1], mod - 2);
    for (int i = MAX_N - 2; i >= 0; i--)
        fac_inv[i] = 1LL * fac_inv[i + 1] * (i + 1) % mod;
}

void dfs(int u, int fa)
{
    siz[u] = 1;
    vector<int> vec;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            dfs(edges[i].to, u), siz[u] += siz[edges[i].to];
            vec.push_back(siz[edges[i].to]);
        }
    int siz = vec.size();
    if (vec.empty())
        vec = vector<int>{1};
    else
        vec = solve(0, siz, vec);
    ans[u] = vec;
    for (int i = 0, siz = vec.size(); i < siz && i <= k; i++)
        dp[u] = (1LL * dp[u] + 1LL * fac[k] * vec[i] % mod * fac_inv[k - i] % mod) % mod;
    return;
}

void dfs_collect(int u, int fa, int have, int del_sum)
{
    gpans = (1LL * gpans + mod - 1LL * dp[u] * del_sum % mod) % mod;
    gpans = (1LL * gpans + 1LL * dp[u] * have % mod) % mod;
    vector<int> n_poly = ans[u];
    n_poly.push_back(0);
    for (int i = n_poly.size() - 2; i >= 0; i--)
        n_poly[i + 1] = (1LL * n_poly[i + 1] + 1LL * n_poly[i] * (n - siz[u]) % mod) % mod;
    map<int, int> press;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa && press.count(siz[edges[i].to]) == 0)
        {
            int calc_dp = 0;
            vector<int> curt = n_poly, nn_poly = curt;
            for (int j = 0, siz_ = nn_poly.size(); j < siz_; j++)
                if (j == 0)
                    nn_poly[j] = curt[j];
                else
                    nn_poly[j] = (1LL * curt[j] + mod - (1LL * nn_poly[j - 1] * siz[edges[i].to] % mod)) % mod;
            for (int j = 0; j < (int)nn_poly.size() && j <= k; j++)
            {
                int vert = k - j;
                int ans = nn_poly[j];
                int cnt = 1LL * fac[k] * ans % mod * fac_inv[vert] % mod;
                calc_dp = (1LL * calc_dp + 1LL * cnt) % mod;
            }
            press[siz[edges[i].to]] = calc_dp;
        }
    puts("");
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dfs_collect(edges[i].to, u, (1LL * have + 1LL * press[siz[edges[i].to]]) % mod, (1LL * del_sum + dp[u]) % mod);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &k), fac_init();
    if (k == 1)
        printf("%lld\n", (1LL * (n - 1) * n / 2) % mod), exit(0);
    for (int i = 1; i <= n - 1; i++)
        scanf("%d%d", &ui[i], &vi[i]);
    for (int i = n - 1; i >= 1; i--)
        addpath(ui[i], vi[i]), addpath(vi[i], ui[i]);
    dfs(1, 0);
    int curt = 0;
    for (int i = 1; i <= n; i++)
    {
        gpans = (1LL * gpans + 1LL * curt * dp[i] % mod) % mod;
        curt = (1LL * curt + 1LL * dp[i]) % mod;
    }
    dfs_collect(1, 0, 0, 0);
    printf("%lld\n", gpans % mod);
    return 0;
}