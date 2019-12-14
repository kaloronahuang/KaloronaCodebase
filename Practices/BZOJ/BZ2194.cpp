// BZ2194.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 4e5 + 200;
const double pi = acos(-1.0);
typedef complex<double> cd;

int n, ai[MAX_N], bi[MAX_N], rev[MAX_N], poly_siz, poly_bit;
cd A[MAX_N], B[MAX_N];

void fft_initialize()
{
    for (int i = 0; i < poly_siz; i++)
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (poly_bit - 1));
}

void fft(cd *arr, int dft)
{
    for (int i = 0; i < poly_siz; i++)
        if (i < rev[i])
            swap(arr[i], arr[rev[i]]);
    for (int step = 1; step < poly_siz; step <<= 1)
    {
        cd omega_n = exp(cd(0, dft * pi / step));
        for (int j = 0; j < poly_siz; j += (step << 1))
        {
            cd omega_nk(1, 0);
            for (int k = j; k < j + step; k++, omega_nk *= omega_n)
            {
                cd t = arr[k + step] * omega_nk;
                arr[k + step] = arr[k] - t;
                arr[k] += t;
            }
        }
    }
    if (dft == -1)
        for (int i = 0; i < poly_siz; i++)
            arr[i] /= poly_siz;
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d%d", &ai[i], &bi[n - i - 1]);
    // prep;
    int len = (n << 1) - 1;
    while ((1 << poly_bit) < len)
        poly_bit++;
    poly_siz = 1 << poly_bit;
    fft_initialize();
    // do;
    for (int i = 0; i < n; i++)
        A[i] = ai[i], B[i] = bi[i];
    fft(A, 1), fft(B, 1);
    for (int i = 0; i < poly_siz; i++)
        A[i] *= B[i];
    fft(A, -1);
    for (int i = n - 1; i < 2 * n - 1; i++)
        printf("%d\n", int(A[i].real() + 0.5));
    return 0;
}