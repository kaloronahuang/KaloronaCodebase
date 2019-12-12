// HDU-4609.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 3e5 + 200;
const double pi = acos(-1.0);

typedef complex<double> cd;

int T, n, ai[MAX_N], coeff[MAX_N], poly_len, poly_bit, rev[MAX_N];
ll bas, ans[MAX_N], prefix[MAX_N];
cd A[MAX_N], B[MAX_N];

void fft_initialize()
{
    for (int i = 0; i < poly_len; i++)
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (poly_bit - 1));
}

void fft(cd *arr, int dft)
{
    for (int i = 0; i < poly_len; i++)
        if (i < rev[i])
            swap(arr[i], arr[rev[i]]);
    for (int step = 1; step < poly_len; step <<= 1)
    {
        cd omega_n = exp(cd(0, dft * pi / step));
        for (int j = 0; j < poly_len; j += (step << 1))
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
        for (int i = 0; i < poly_len; i++)
            arr[i] /= poly_len;
}

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        memset(coeff, 0, sizeof(coeff));
        scanf("%d", &n), bas = 1LL * n * (n - 1) * (n - 2) / 6;
        int mx = 0;
        for (int i = 1; i <= n; i++)
            scanf("%d", &ai[i]), coeff[ai[i]]++, mx = max(mx, ai[i]);
        sort(ai + 1, ai + 1 + n);
        // prepare for the poly;
        mx++, poly_len = poly_bit = 0;
        while ((1 << poly_bit) < 2 * mx)
            poly_bit++;
        poly_len = 1 << poly_bit;
        for (int i = 0; i < mx; i++)
            A[i] = cd(coeff[i], 0);
        for (int i = mx; i < poly_len; i++)
            A[i] = cd(0, 0);

        // go!
        fft_initialize(), fft(A, 1);
        for (int i = 0; i < poly_len; i++)
            A[i] = A[i] * A[i];
        fft(A, -1);
        for (int i = 0; i < poly_len; i++)
            ans[i] = (ll)(A[i].real() + 0.5);
        for (int i = 1; i <= n; i++)
            ans[ai[i] + ai[i]]--;
        for (int i = 0; i < poly_len; i++)
            ans[i] /= 2LL, prefix[i] = prefix[i - 1] + ans[i];
        ll numerator = 0;
        for (int i = 1; i <= n; i++)
        {
            numerator += prefix[poly_len - 1] - prefix[ai[i]];
            numerator -= 1LL * (i - 1) * (n - i);
            numerator -= (n - 1);
            numerator -= 1LL * (n - i) * (n - i - 1) / 2;
        }

        printf("%.7lf\n", double(numerator) / double(bas));
    }
    return 0;
}