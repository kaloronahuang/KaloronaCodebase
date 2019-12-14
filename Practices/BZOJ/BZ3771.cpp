// BZ3771.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 301000;
const double pi = acos(-1.0);
typedef complex<double> cd;

int n, ai[MAX_N], sol[MAX_N][5], rev[MAX_N], poly_siz, poly_bit, len;
cd A[MAX_N], B[MAX_N];

void clear(cd *arr)
{
    for (int i = 0; i < poly_siz; i++)
        arr[i] = cd(0, 0);
}

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
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]), len = max(len, ai[i]), sol[ai[i]][1]++;
    len++, len *= 3;
    while ((1 << poly_bit) < len)
        poly_bit++;
    poly_siz = 1 << poly_bit;
    fft_initialize();
    // go!
    // double;
    for (int i = 1; i <= n; i++)
        A[ai[i]] = cd(1, 0);
    fft(A, 1);
    for (int i = 0; i < poly_siz; i++)
        A[i] *= A[i];
    fft(A, -1);
    // collect;
    for (int i = 0; i < poly_siz; i++)
        sol[i][2] += int(A[i].real() + 0.5);
    for (int i = 1; i <= n; i++)
        sol[ai[i] + ai[i]][2]--;
    for (int i = 0; i < poly_siz; i++)
        sol[i][2] /= 2;
    // triple;
    clear(A);
    for (int i = 0; i < poly_siz; i++)
        A[i] = cd(sol[i][2], 0);
    for (int i = 1; i <= n; i++)
        B[ai[i]] = cd(1, 0);
    fft(A, 1), fft(B, 1);
    for (int i = 0; i < poly_siz; i++)
        A[i] *= B[i];
    fft(A, -1);
    for (int i = 0; i < poly_siz; i++)
        sol[i][3] = int(A[i].real() + 0.5);
    clear(A), clear(B);
    // delete the fail stats;
    for (int i = 1; i <= n; i++)
        A[ai[i] + ai[i]] = cd(1, 0), B[ai[i]] = cd(1, 0);
    fft(A, 1), fft(B, 1);
    for (int i = 0; i < poly_siz; i++)
        A[i] *= B[i];
    fft(A, -1);
    for (int i = 0; i < poly_siz; i++)
        sol[i][4] = int(A[i].real() + 0.5);
    for (int i = 1; i <= n; i++)
        sol[ai[i] * 3][4]--;
    for (int i = 0; i < poly_siz; i++)
        sol[i][3] -= sol[i][4], sol[i][3] /= 3;
    for (int i = 0; i < poly_siz; i++)
        if (sol[i][1] + sol[i][2] + sol[i][3] > 0)
            printf("%d %d\n", i, (sol[i][1] + sol[i][2] + sol[i][3]));
    return 0;
}