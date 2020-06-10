// P1919.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 8e6 + 200, mod = 998244353, G = 3;

int poly_siz, poly_bit, rev[MAX_N], tA[MAX_N], tB[MAX_N];
char str[2][MAX_N];

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

const int invG = fpow(G, mod - 2);

void ntt_initialize()
{
    for (int i = 0; i < poly_siz; i++)
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (poly_bit - 1));
}

void ntt(int *arr, int dft)
{
    for (int i = 0; i < poly_siz; i++)
        if (i < rev[i])
            swap(arr[i], arr[rev[i]]);
    for (int step = 1; step < poly_siz; step <<= 1)
    {
        int omega_n = fpow(dft == 1 ? G : invG, (mod - 1) / (step << 1));
        for (int j = 0; j < poly_siz; j += (step << 1))
        {
            int omega_nk = 1;
            for (int k = j; k < j + step; k++, omega_nk = 1LL * omega_nk * omega_n % mod)
            {
                int t = 1LL * arr[k + step] * omega_nk % mod;
                arr[k + step] = (0LL + arr[k] + mod - t) % mod, arr[k] = (0LL + arr[k] + t) % mod;
            }
        }
    }
    if (dft == -1)
    {
        int inv = fpow(poly_siz, mod - 2);
        for (int i = 0; i < poly_siz; i++)
            arr[i] = 1LL * arr[i] * inv % mod;
    }
}

int main()
{
    /*
    freopen("P1919_1.in", "r", stdin);
    freopen("test.out", "w", stdout);
    */
    scanf("%s%s", str[0], str[1]);
    int n = strlen(str[0]), m = strlen(str[1]);
    int len = (n + m) << 1;
    poly_siz = 1, poly_bit = 0;
    while (poly_siz <= len)
        poly_siz <<= 1, poly_bit++;
    for (int i = 0; i < n; i++)
        tA[i] = str[0][n - i - 1] - '0';
    for (int i = 0; i < m; i++)
        tB[i] = str[1][m - i - 1] - '0';
    ntt_initialize();
    ntt(tA, 1), ntt(tB, 1);
    for (int i = 0; i < poly_siz; i++)
        tA[i] = 1LL * tA[i] * tB[i] % mod;
    ntt(tA, -1);
    string str;
    int ptr = ((n + m) << 1) - 1;
    for (int i = 0; i < poly_siz; i++)
        tA[i + 1] += tA[i] / 10, tA[i] %= 10;
    for (; ptr >= 1; ptr--)
        if (tA[ptr] != 0)
            break;
    for (int i = ptr; i >= 0; i--)
        str += '0' + tA[i];
    cout << str << endl;
    return 0;
}