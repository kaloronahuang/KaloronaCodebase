// BZ5058.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 500100, mod = 1e9 + 7;

int n, swap_time, seq[MAX_N];

inline char gc()
{
    static char buf[1000000], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1000000, stdin), p1 == p2) ? EOF : *p1++;
}

int read()
{
    int x = 0, f = 1;
    char ch = gc();
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = gc();
    }
    while (isdigit(ch))
        x = (x << 3) + (x << 1) + ch - '0', ch = gc();
    return f * x;
}

struct BIT
{

    int nodes[MAX_N];

#define lowbit(x) (x & (-x))

    void update(int x, int d)
    {
        for (; x <= n; x += lowbit(x))
            nodes[x] = (0LL + nodes[x] + d) % mod;
    }

    int query(int x, int ret = 0)
    {
        for (; x; x -= lowbit(x))
            ret = (0LL + ret + nodes[x]) % mod;
        return ret;
    }
} tr[3];

struct matrix
{
    int mat[7][7];

    void clear() { memset(mat, 0, sizeof(mat)); }

    int *operator[](const int &rhs) { return mat[rhs]; }

    matrix operator*(const matrix &rhs)
    {
        matrix ret;
        ret.clear();
        for (int i = 0; i < 7; i++)
            for (int j = 0; j < 7; j++)
                for (int k = 0; k < 7; k++)
                    ret[i][j] = (1LL * ret[i][j] + 1LL * mat[i][k] * rhs.mat[k][j] % mod) % mod;
        return ret;
    }

    matrix operator^(const int &rhs)
    {
        matrix ret, bas = *this;
        ret.clear();
        for (int i = 0; i < 7; i++)
            ret[i][i] = 1;
        int tim = rhs;
        while (tim)
        {
            if (tim & 1)
                ret = ret * bas;
            bas = bas * bas;
            tim >>= 1;
        }
        return ret;
    }
};

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

const int inv2 = quick_pow(2, mod - 2);

int choose2(int n) { return 1LL * n * (n - 1) % mod * inv2 % mod; }

matrix build()
{
    matrix ret;
    int curt[7][7] = {
        {choose2(n - 2), n - 2, 1, 0, 0, n - 2, 0},
        {1, (choose2(n - 2) + n - 3) % mod, 0, 1, 1, 0, n - 3},
        {1, 0, choose2(n - 2), n - 2, n - 2, 0, 0},
        {0, 1, 1, (choose2(n - 2) + n - 3) % mod, 0, 1, n - 3},
        {0, 1, 1, 0, (choose2(n - 2) + n - 3) % mod, 1, n - 3},
        {1, 0, 0, 1, 1, (choose2(n - 2) + n - 3) % mod, n - 3},
        {0, 1, 0, 1, 1, 1, (0LL + choose2(n - 2) + 2LL * (n - 4) % mod + 1) % mod}};
    memcpy(ret.mat, curt, sizeof(curt));
    return ret ^ swap_time;
}

int main()
{
    n = read(), swap_time = read();
    for (int i = 1; i <= n; i++)
        seq[i] = read();
    matrix ans = build();
    int gans = 0, f_sum = 0, g_sum = 0, inv = quick_pow(n - 2, mod - 2);
    for (int i = 1; i <= n; i++)
    {
        int num_a = tr[0].query(seq[i]), f_a = tr[1].query(seq[i]), g_a = tr[2].query(seq[i]);
        int num_b = i - 1 - num_a, f_b = (0LL + f_sum + mod - f_a) % mod, g_b = (0LL + g_sum + mod - g_a) % mod;

        gans = (0LL + gans + 1LL * ans[0][0] * num_b % mod) % mod;
        gans = (0LL + gans + 1LL * ans[0][1] * ((0LL + f_a + g_b) % mod) % mod * inv % mod) % mod;
        gans = (0LL + gans + 1LL * ans[0][2] * num_a % mod) % mod;
        gans = (0LL + gans + 1LL * ans[0][3] * ((0LL + f_b + g_a) % mod) % mod * inv % mod) % mod;
        gans = (0LL + gans + 1LL * (1LL * num_a * (i - 2) % mod + 1LL * num_b * (n - i) % mod) % mod * ans[0][4] % mod * inv % mod) % mod;
        gans = (0LL + gans + 1LL * (1LL * num_b * (i - 2) % mod + 1LL * num_a * (n - i) % mod) % mod * ans[0][5] % mod * inv % mod) % mod;

        tr[0].update(seq[i], 1), tr[1].update(seq[i], i - 1), tr[2].update(seq[i], n - i - 1);
        f_sum = (0LL + f_sum + i - 1) % mod, g_sum = (0LL + g_sum + n - i - 1) % mod;
    }
    gans = (0LL + gans + 1LL * choose2(n) * quick_pow(2, mod - 2) % mod * ans[0][6] % mod) % mod;
    printf("%d\n", gans);
    return 0;
}