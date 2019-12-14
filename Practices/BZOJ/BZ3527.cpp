// BZ3527.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 400100;
const double pi = acos(-1.0);
typedef complex<double> cd;

int n, rev[MAX_N], poly_bit, poly_siz;
double qi[MAX_N], ans[MAX_N];
cd A[MAX_N], B[MAX_N], C[MAX_N], D[MAX_N];

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

double pow2(double x) { return x * x; }

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lf", &qi[i]);

    int len = 2 * n - 1;
    while ((1 << poly_bit) < len)
        poly_bit++;
    poly_siz = (1 << poly_bit);
    fft_initialize();
    for (int i = 0; i < n; i++)
        A[i] = qi[i + 1], B[i] = 1.0 / pow2(i + 1);
    fft(A, 1), fft(B, 1);
    for (int i = 0; i < poly_siz; i++)
        A[i] = A[i] * B[i];
    fft(A, -1);
    for (int i = 2; i <= n; i++)
        ans[i] += A[i - 2].real();
    for (int i = 0; i <= poly_siz; i++)
        A[i] = B[i] = cd(0, 0);
    for (int i = 0; i < n; i++)
        A[i] = qi[n - i], B[i] = 1.0 / pow2(i + 1);
    fft(A, 1), fft(B, 1);
    for (int i = 0; i < poly_siz; i++)
        A[i] = A[i] * B[i];
    fft(A, -1);
    for (int i = n - 1; i >= 1; i--)
        ans[i] -= A[n - i - 1].real();
    for (int i = 1; i <= n; i++)
        printf("%.3lf\n", ans[i]);
    return 0;
}