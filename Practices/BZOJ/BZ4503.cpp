// BZ4503.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 4e5 + 200;
const double pi = acos(-1.0);
typedef complex<double> cd;

int n, m, poly_siz, poly_bit, rev[MAX_N], f[MAX_N], ai[MAX_N], bi[MAX_N];
char str1[MAX_N], str2[MAX_N];
cd A[MAX_N], B[MAX_N];

double pow2(double x) { return x * x; }

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

void clear(cd *arr)
{
    for (int i = 0; i < poly_siz; i++)
        arr[i] = cd(0, 0);
}

int main()
{
    scanf("%s%s", str1, str2);
    n = strlen(str1), m = strlen(str2);
    reverse(str2, str2 + m);

    int len = n + m;
    while ((1 << poly_bit) < len)
        poly_bit++;
    poly_siz = 1 << poly_bit;
    fft_initialize();

    for (int i = 0; i < n; i++)
        ai[i] = str1[i] - 'a' + 1;
    for (int i = 0; i < m; i++)
        bi[i] = ((str2[i] == '?') ? 0 : str2[i] - 'a' + 1);

    for (int i = 0; i < n; i++)
        A[i] = pow2(ai[i]);
    for (int i = 0; i < m; i++)
        B[i] = bi[i];
    fft(A, 1), fft(B, 1);
    for (int i = 0; i < poly_siz; i++)
        A[i] *= B[i];
    fft(A, -1);
    for (int i = 0; i < n; i++)
        f[i] = (ll)(A[i].real() + 0.5);
    clear(A), clear(B);

    for (int i = 0; i < n; i++)
        A[i] = ai[i];
    for (int i = 0; i < m; i++)
        B[i] = pow2(bi[i]);
    fft(A, 1), fft(B, 1);
    for (int i = 0; i < poly_siz; i++)
        A[i] *= B[i];
    fft(A, -1);
    for (int i = 0; i < poly_siz; i++)
        f[i] -= 2LL * int(A[i].real() + 0.5);
    clear(A), clear(B);

    ll bas = 0;
    for (int i = 0; i < m; i++)
        bas += 1LL * bi[i] * bi[i] * bi[i];

    for (int i = 0; i < n; i++)
        f[i] += bas;

    int cnt = 0;
    for (int i = 0; i < n; i++)
        cnt += (f[i] == 0 && i - m + 1 >= 0);
    printf("%d\n", cnt);
    for (int i = 0; i < n; i++)
        if (f[i] == 0 && i - m + 1 >= 0)
            printf("%d\n", i - m + 1);
    return 0;
}