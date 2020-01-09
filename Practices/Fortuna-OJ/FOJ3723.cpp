// FOJ3723.cpp
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")

using namespace std;

typedef complex<double> cd;
const int MAX_N = 2e5 + 200;
const double Pi = acos(-1.0);

int n, ai[MAX_N], bi[MAX_N], cnt1[MAX_N], cnt2[MAX_N];
int a2, a3, a4, a5;
int b2, b3, b4, b5;
int anses[MAX_N];
pair<int, int> As[MAX_N], Bs[MAX_N];
cd A[MAX_N << 1], B[MAX_N << 1];

int poly_siz, poly_bit, rev[MAX_N << 1];

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
        cd omega_n = exp(cd(0, dft * Pi / step));
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

void fileIO() { freopen("sum.in", "r", stdin), freopen("sum.out", "w", stdout); }

int main()
{
    fileIO();
    while (scanf("%d", &n) != EOF)
    {
        memset(cnt1, 0, sizeof(cnt1)), memset(cnt2, 0, sizeof(cnt2));
        memset(anses, 0, sizeof(anses));
        scanf("%d%d%d%d%d%d", &ai[1], &ai[2], &a2, &a3, &a4, &a5);
        scanf("%d%d%d%d%d%d", &bi[1], &bi[2], &b2, &b3, &b4, &b5);
        int a_max = 0, b_max = 0;
        for (int i = 3; i <= n; i++)
        {
            ai[i] = (1LL * ai[i - 1] * a2 % a5 + 1LL * ai[i - 2] * a3 % a5 + a4) % a5;
            bi[i] = (1LL * bi[i - 1] * b2 % b5 + 1LL * bi[i - 2] * b3 % b5 + b4) % b5;
        }
        for (int i = 1; i <= n; i++)
        {
            cnt1[ai[i]]++, cnt2[bi[i]]++;
            a_max = max(a_max, ai[i]), b_max = max(b_max, bi[i]);
        }
        // first stage for bigger k;
        int atot = 0, btot = 0;
        for (int i = 0; i <= a_max; i++)
            if (cnt1[i] >= 10)
                As[++atot] = make_pair(i, cnt1[i]);
        for (int i = 0; i <= b_max; i++)
            if (cnt2[i] >= 10)
                Bs[++btot] = make_pair(i, cnt2[i]);
        for (int i = 1; i <= atot; i++)
            for (int j = 1; j <= btot; j++)
                anses[As[i].first + Bs[j].first] += min(As[i].second, Bs[j].second) - 9;
        // second stage for smaller k;
        int len = a_max + b_max + 1;
        poly_siz = poly_bit = 0;
        while ((1 << poly_bit) < len)
            poly_bit++;
        poly_siz = (1 << poly_bit);
        fft_initialize();
        for (int k = 1; k < 10; k++)
        {
            for (int i = 0; i < poly_siz; i++)
                A[i] = B[i] = 0;
            for (int i = 0; i <= a_max; i++)
                A[i] = (cnt1[i] >= k);
            for (int i = 0; i <= b_max; i++)
                B[i] = (cnt2[i] >= k);
            fft(A, 1), fft(B, 1);
            for (int i = 0; i < poly_siz; i++)
                A[i] = A[i] * B[i];
            fft(A, -1);
            for (int i = 0; i < poly_siz; i++)
                anses[i] += int(A[i].real() + 1e-6);
        }
        int X = 0, Y = 0;
        for (int i = 0; i <= a_max + b_max; i++)
            if (anses[i] >= X)
                X = anses[i], Y = i;
        printf("%d %d\n", X, Y);
    }
    return 0;
}