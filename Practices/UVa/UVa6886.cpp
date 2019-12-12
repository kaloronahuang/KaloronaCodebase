// UVa6886.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;
const double pi = acos(-1.0);

typedef complex<double> cd;
typedef cd *poly;

int rev[MAX_N], n, m, poly_len, mx_bit, ki[MAX_N], ai[MAX_N];

void fft_initialize()
{
    for (int i = 0; i < (1 << mx_bit); i++)
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (mx_bit - 1));
}

void fft(poly p, int dft)
{
    for (int i = 0; i < poly_len; i++)
        if (i < rev[i])
            swap(p[i], p[rev[i]]);
    for (int step = 1; step < poly_len; step <<= 1)
    {
        cd omega_n = exp(cd(0, dft * pi / step));
        for (int j = 0; j < poly_len; j += (step << 1))
        {
            cd omega_nk = cd(1, 0);
            for (int k = j; k < j + step; k++, omega_nk *= omega_n)
            {
                cd t = omega_nk * p[k + step];
                p[k + step] = p[k] - t;
                p[k] += t;
            }
        }
    }
    if (dft == -1)
        for (int i = 0; i < poly_len; i++)
            p[i] /= poly_len;
}

cd A[MAX_N];

int main()
{
    while (~scanf("%d", &n))
    {
        memset(rev, 0, sizeof(rev)), memset(ai, 0, sizeof(ai));
        int len = 0;
        for (int i = 1; i <= n; i++)
            scanf("%d", &ki[i]), len = max(len, ki[i] + 1), ai[ki[i]] = 1;
        for (mx_bit = 0; (1 << mx_bit) < (len << 1); mx_bit++)
            ;
        poly_len = (1 << mx_bit);
        ai[0] = 1;
        for (int i = 0; i < len; i++)
            A[i] = cd(ai[i], 0);
        for (int i = len; i < poly_len; i++)
            A[i] = cd(0, 0);
        fft_initialize(), fft(A, 1);
        for (int i = 0; i < poly_len; i++)
            A[i] = A[i] * A[i];
        fft(A, -1);
        scanf("%d", &m);
        int cnt = 0;
        for (int i = 1, val; i <= m; i++)
        {
            scanf("%d", &val);
            if (int(A[val].real() + 0.5))
                cnt++;
        }
        printf("%d\n", cnt);
    }
    return 0;
}