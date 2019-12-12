// HDU-1402.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 200100;
const double Pi = acos(-1.0);

typedef complex<double> cd;
typedef vector<cd> poly;

int rev[MAX_N], ans[MAX_N];
char opt[MAX_N], str[MAX_N];

// gurantee that len = 2^k;
void fft(poly &p, int dft)
{
    // preperation;
    int mx_bit, len = p.size();
    for (mx_bit = 1; (1 << mx_bit) < len; mx_bit++)
        ;
    for (int i = 0; i < (1 << mx_bit); i++)
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (mx_bit - 1));
    for (int i = 0; i < (1 << mx_bit); i++)
        if (i < rev[i])
            swap(p[i], p[rev[i]]);
    // start;
    for (int step = 1; step < len; step <<= 1)
    {
        cd omega_n = exp(cd(0, dft * Pi / step));
        for (int j = 0; j < len; j += (step << 1))
        {
            cd omega_nk(1, 0);
            for (int k = j; k < j + step; k++, omega_nk *= omega_n)
            {
                cd t = omega_nk * p[k + step];
                p[k + step] = p[k] - t;
                p[k] += t;
            }
        }
    }
    if (dft == -1)
        for (int i = 0; i < len; i++)
            p[i] /= len;
}

int main()
{
    while (scanf("%s", opt) != EOF)
    {
        memset(ans, 0, sizeof(ans)), memset(rev, 0, sizeof(rev));
        scanf("%s", str);
        int n = strlen(opt), m = strlen(str), glen = n + m - 1, mbit;
        for (mbit = 1; (1 << mbit) < glen; mbit++)
            mbit++;
        poly A(1 << mbit), B(1 << mbit);
        for (int i = n - 1; i >= 0; i--)
            A[n - i - 1].real(opt[i] - '0');
        for (int i = m - 1; i >= 0; i--)
            B[m - i - 1].real(str[i] - '0');
        fft(A, 1), fft(B, 1);
        for (int i = 0; i < (1 << mbit); i++)
            A[i] *= B[i];
        fft(A, -1);
        for (int i = 0; i < (1 << mbit); i++)
            ans[i] = int(A[i].real() + 0.5);
        for (int i = 0; i < (1 << mbit) - 1; i++)
            ans[i + 1] += (ans[i] / 10), ans[i] %= 10;
        int pos = (1 << mbit) - 1;
        for (; pos >= 1; pos--)
            if (ans[pos] != 0)
                break;
        for (; pos >= 0; pos--)
            printf("%d", ans[pos]);
        puts("");
    }
    return 0;
}