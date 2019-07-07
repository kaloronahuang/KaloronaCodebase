// LOJ108.cpp
#include <bits/stdc++.h>

using namespace std;

typedef complex<double> cd;

const double Pi = acos(-1.0);
const int MAX_N = 3e5 + 2000;

cd A[MAX_N], B[MAX_N];
int n, m, rev[MAX_N], max_bit, max_power;

void fft_initialize()
{
    for (max_bit = 1, max_power = 2; (1 << max_bit) < n + m - 1; max_bit++)
        max_power <<= 1;
    for (int i = 0; i < max_power; i++)
        rev[i] = ((rev[i >> 1] >> 1) | ((i & 1) << (max_bit - 1)));
}

void fft(cd *arr, int len, int dft)
{
    for (int i = 0; i < len; i++)
        if (i < rev[i])
            swap(arr[i], arr[rev[i]]);
    for (int step = 1; step < len; step <<= 1)
    {
        cd omega_n = exp(cd(0, dft * Pi / step));
        for (int j = 0; j < len; j += (step << 1))
        {
            cd omega_nk(1, 0);
            for (int k = j; k < j + step; k++, omega_nk *= omega_n)
            {
                cd t = omega_nk * arr[k + step];
                arr[k + step] = arr[k] - t;
                arr[k] += t;
            }
        }
    }
    if (dft == -1)
        for (int i = 0; i < len; i++)
            arr[i] /= len;
}

int main()
{
    scanf("%d%d", &n, &m), n++, m++, fft_initialize();
    for (int i = 0, tmp; i < n; i++)
        scanf("%d", &tmp), A[i].real(tmp);
    for (int i = 0, tmp; i < m; i++)
        scanf("%d", &tmp), B[i].real(tmp);
    fft(A, max_power, 1), fft(B, max_power, 1);
    for (int i = 0; i < max_power; i++)
        A[i] *= B[i];
    fft(A, max_power, -1);
    for (int i = 0; i < n + m - 1; i++)
        printf("%d ", (int)(A[i].real() + 0.5));
    return 0;
}