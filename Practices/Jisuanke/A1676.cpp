// A1676.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 4e6 + 200;
const double pi = acos(-1.0);
typedef complex<double> cd;

int n, m, poly_bit, poly_siz, rev[MAX_N], gainedPoints[MAX_N];
char str[MAX_N], opt[MAX_N];
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

void build(char win, char lose)
{
    for (int i = 0; i < poly_siz; i++)
    {
        A[i] = (i < n && str[i] == lose) ? cd(1, 0) : cd(0, 0);
        B[i] = (i < m && opt[i] == win) ? cd(1, 0) : cd(0, 0);
    }
    fft(A, 1), fft(B, 1);
    for (int i = 0; i < poly_siz; i++)
        A[i] = A[i] * B[i];
    fft(A, -1);
    for (int i = 0; i < poly_siz; i++)
        gainedPoints[i] += int(A[i].real() + 0.5);
    return;
}

int main()
{
    scanf("%s%s", str, opt);
    n = strlen(str), m = strlen(opt);
    for (int i = 0; i < (m >> 1); i++)
        swap(opt[i], opt[m - i - 1]);
    int len = max(n, m) + 1;
    while ((1 << poly_bit) < (len << 1))
        poly_bit++;
    poly_siz = (1 << poly_bit);
    fft_initialize();
    build('S', 'P'), build('P', 'R'), build('R', 'L'), build('R', 'S');
    build('L', 'K'), build('K', 'S'), build('S', 'L'), build('L', 'P');
    build('P', 'K'), build('K', 'R');
    int ans = 0;
    for (int i = m - 1; i < n; i++)
        ans = max(ans, gainedPoints[i]);
    printf("%d\n", ans);
    return 0;
}