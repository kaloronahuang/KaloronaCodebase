// CF954I.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e5 + 200;
const double pi = acos(-1.0);
typedef complex<double> cd;

int n, m, poly_bit, poly_siz, fa[MAX_N][10], rev[MAX_N], acc[MAX_N];
cd A[MAX_N], B[MAX_N];
char str[MAX_N], opt[MAX_N];
set<int> st[MAX_N];

void fft_initialize()
{
    for (int i = 0; i < poly_siz; i++)
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (poly_bit - 1));
}

int find(int typ, int id) { return fa[typ][id] == id ? id : fa[typ][id] = find(typ, fa[typ][id]); }

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

void build(char l, char r)
{
    for (int i = 0; i < poly_siz; i++)
    {
        A[i] = (i < n && str[i] == l) ? cd(1, 0) : cd(0, 0);
        B[i] = (i < m && opt[i] == r) ? cd(1, 0) : cd(0, 0);
    }
    fft(A, 1), fft(B, 1);
    for (int i = 0; i < poly_siz; i++)
        A[i] *= B[i];
    fft(A, -1);
    for (int i = 0; i < poly_siz; i++)
        acc[i] = int(A[i].real() + 0.5);
}

int main()
{
    scanf("%s%s", str, opt);
    n = strlen(str), m = strlen(opt);
    int len = max(n, m) + 1;
    reverse(opt, opt + m);
    while ((1 << poly_bit) < (len << 1))
        poly_bit++;
    poly_siz = (1 << poly_bit);
    for (int i = m - 1; i < n; i++)
        for (int d = 0; d < 6; d++)
            fa[i][d] = d;
    fft_initialize();
    for (int u = 0; u < 6; u++)
        for (int v = 0; v < 6; v++)
        {
            build(u + 'a', v + 'a');
            // build graph;
            for (int i = m - 1; i < n; i++)
                if (acc[i] > 0)
                {
                    int x = find(i, u), y = find(i, v);
                    fa[i][x] = fa[i][y];
                    st[i].insert(u), st[i].insert(v);
                }
        }
    for (int i = m - 1; i < n; i++)
    {
        int components = 0;
        for (int d = 0; d < 6; d++)
            if (find(i, d) == d && st[i].count(d))
                components++;
        printf("%lld ", 1LL * st[i].size() - components);
    }
    return 0;
}