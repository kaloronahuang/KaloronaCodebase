// BZ3513.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 304000;
const double pi = acos(-1.0);
typedef complex<double> cd;

int T, n, ai[MAX_N], poly_siz, poly_bit, rev[MAX_N];
ll prefix[MAX_N], val[MAX_N], sol[MAX_N];
cd A[MAX_N];

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
                cd t = omega_nk * arr[k + step];
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
    scanf("%d", &T);
    while (T--)
    {
        memset(sol, 0, sizeof(sol));
        memset(val, 0, sizeof(val));
        scanf("%d", &n), poly_bit = 0;
        for (int i = 1; i <= n; i++)
            scanf("%d", &ai[i]), val[ai[i]]++;
        sort(ai + 1, ai + 1 + n);
        int len = (ai[n] + 1) << 1;
        while ((1 << poly_bit) < len)
            poly_bit++;
        poly_siz = 1 << poly_bit, clear(A);
        fft_initialize();
        for (int i = 0; i < poly_siz; i++)
            A[i] = val[i];
        fft(A, 1);
        for (int i = 0; i < poly_siz; i++)
            A[i] *= A[i];
        fft(A, -1);
        for (int i = 0; i < poly_siz; i++)
            sol[i] = int(A[i].real() + 0.5);
        for (int i = 1; i <= n; i++)
            sol[ai[i] << 1]--;
        for (int i = 0; i < poly_siz; i++)
            sol[i] >>= 1;
        prefix[0] = sol[0];
        for (int i = 1; i < poly_siz; i++)
            prefix[i] = prefix[i - 1] + sol[i];
        ll ans = 0;
        for (int i = 1; i <= n; i++)
            ans += prefix[poly_siz - 1] - prefix[ai[i]];
        for (int i = 1; i <= n; i++)
        {
            ans -= 1LL * (n - i) * (i - 1);
            ans -= n - 1;
            ans -= 1LL * (n - i) * (n - i - 1) / 2;
        }
        printf("%.7lf\n", double(ans) / double(1LL * n * (n - 1) * (n - 2) / 6));
    }
    return 0;
}