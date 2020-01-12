// P3723.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;
const double pi = acos(-1.0);
typedef complex<double> cd;
typedef long long ll;

int n, m, ai[MAX_N], bi[MAX_N], poly_bit, poly_siz, rev[MAX_N];
ll res[MAX_N];
cd A[MAX_N], B[MAX_N];

void fft_initialize()
{
    for (int i = 0; i < poly_siz; i++)
        rev[i] = ((rev[i >> 1] >> 1) | ((i & 1) << (poly_bit - 1)));
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
                arr[k + step] = arr[k] - t, arr[k] += t;
            }
        }
    }
    if (dft == -1)
        for (int i = 0; i < poly_siz; i++)
            arr[i] /= poly_siz;
}

ll pow2(ll bas) { return bas * bas; }

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    for (int i = 1; i <= n; i++)
        scanf("%d", &bi[i]);
    ll ai_sum = 0, bi_sum = 0, diff = 0;
    for (int i = 1; i <= n; i++)
        ai_sum += pow2(ai[i]), bi_sum += pow2(bi[i]), diff += ai[i] - bi[i];
    reverse(bi + 1, bi + 1 + n);
    for (int i = 1; i <= n; i++)
        A[i] = A[i + n] = ai[i], B[i] = bi[i];
    while ((1 << poly_bit) <= (n * 3))
        poly_bit++;
    poly_siz = (1 << poly_bit);
    fft_initialize();
    fft(A, 1), fft(B, 1);
    for (int i = 0; i < poly_siz; i++)
        A[i] *= B[i];
    fft(A, -1);
    for (int i = 0; i < poly_siz; i++)
        res[i] = ll(A[i].real() + 0.5);
    ll ans = 0x7fffffffffffffff;
    for (int delta = -m; delta <= m; delta++)
        for (int rotation = 1; rotation <= n; rotation++)
            ans = min(ans, ai_sum + bi_sum + pow2(delta) * n + 2LL * diff * delta - 2LL * res[n + rotation]);
    printf("%lld\n", ans);
    return 0;
}