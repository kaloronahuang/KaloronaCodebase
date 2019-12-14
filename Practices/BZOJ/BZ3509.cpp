// BZ3509.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 4e5 + 200;
const double pi = acos(-1.0);
typedef complex<double> cd;

int n, ai[MAX_N], bucket[MAX_N], aff[MAX_N], lft[MAX_N], rig[MAX_N], block_siz;
int poly_siz, poly_bit, rev[MAX_N], mp[MAX_N];
cd A[MAX_N], B[MAX_N];

inline char nc()
{
    static char buf[1000000], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1000000, stdin), p1 == p2) ? EOF : *p1++;
}

int read()
{
    int x = 0, f = 1;
    char ch = nc();
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = nc();
    }
    while (isdigit(ch))
        x = (x << 3) + (x << 1) + ch - '0', ch = nc();
    return x * f;
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

void clear(cd *arr)
{
    for (int i = 0; i < poly_siz; i++)
        arr[i] = cd(0, 0);
}

int main()
{
    int len = 0;
    n = read(), block_siz = sqrt(n * 300);
    for (int i = 1; i <= n; i++)
    {
        ai[i] = read();
        int bid = (i - 1) / block_siz + 1;
        lft[bid] = ((lft[bid] == 0) ? i : lft[bid]);
        rig[bid] = i, aff[i] = bid, len = max(len, ai[i]);
    }
    while ((1 << poly_bit) < (len << 1))
        poly_bit++;
    poly_siz = 1 << poly_bit;
    fft_initialize();

    ll ans = 0;
    for (int idx = 1; idx <= aff[n]; idx++)
        for (int i = lft[idx]; i <= rig[idx]; i++)
        {
            for (int k = i + 1; k <= rig[idx]; k++)
            {
                int tmp = (ai[i] << 1) - ai[k];
                if (tmp >= 0)
                    ans += mp[tmp];
            }
            ++mp[ai[i]];
        }
    memset(mp, 0, sizeof(mp));
    for (int idx = aff[n]; idx >= 1; idx--)
        for (int i = rig[idx]; i >= lft[idx]; i--)
        {
            for (int k = i - 1; k >= lft[idx]; k--)
            {
                int tmp = (ai[i] << 1) - ai[k];
                if (tmp >= 0)
                    ans += mp[tmp];
            }
            mp[ai[i]]++;
        }
    memset(mp, 0, sizeof(mp));
    for (int idx = 1; idx <= aff[n]; idx++)
    {
        for (int i = lft[idx]; i <= rig[idx]; i++)
        {
            for (int k = i + 1; k <= rig[idx]; k++)
            {
                int tmp = (ai[i] << 1) - ai[k];
                if (tmp >= 0)
                    ans -= mp[tmp];
            }
            mp[ai[i]]++;
        }
        for (int i = lft[idx]; i <= rig[idx]; i++)
            mp[ai[i]]--;
    }
    for (int idx = 1; idx <= aff[n]; idx++)
    {
        clear(A), clear(B);
        for (int i = 1; i <= lft[idx] - 1; i++)
            A[ai[i]].real(A[ai[i]].real() + 1);
        for (int i = rig[idx] + 1; i <= n; i++)
            B[ai[i]].real(B[ai[i]].real() + 1);
        fft(A, 1), fft(B, 1);
        for (int i = 0; i < poly_siz; i++)
            A[i] *= B[i];
        fft(A, -1);
        for (int i = lft[idx]; i <= rig[idx]; i++)
            ans += (ll)(A[ai[i] + ai[i]].real() + 0.5);
    }
    printf("%lld\n", ans);
    return 0;
}