// UVa4671.cpp
#include <bits/stdc++.h>
#define ull unsigned long long

using namespace std;

const int MAX_N = 1e6 + 200, bitnum = 3;
const double pi = acos(-1.0);
typedef complex<double> cd;

int k, n, m, rev[MAX_N], poly_len, poly_bit, res[MAX_N];
char str[MAX_N], opt[MAX_N];
cd A[MAX_N], B[MAX_N];
ull pow_magic[MAX_N], prefix[MAX_N];

inline void fft_initialize()
{
    for (int i = 0; i < poly_len; i++)
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (poly_bit - 1));
}

inline void fft(cd *arr, int dft)
{
    for (int i = 0; i < poly_len; i++)
        if (i < rev[i])
            swap(arr[i], arr[rev[i]]);
    for (int step = 1; step < poly_len; step <<= 1)
    {
        cd omega_n = exp(cd(0, dft * pi / step));
        for (int j = 0; j < poly_len; j += (step << 1))
        {
            cd omega_nk = cd(1, 0);
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

inline void dft()
{
    fft(A, 1), fft(B, 1);
    for (int i = 0; i < poly_len; i++)
        A[i] = A[i] * B[i];
    fft(A, -1);
    for (int i = 0; i < poly_len; i++)
        res[i] += int(A[i].real() + 0.5);
}

inline void build(char typ1, char typ2)
{
    for (int i = 0; i < poly_len; i++)
    {
        A[i] = (i < n && str[i] == typ1) ? cd(1, 0) : cd(0, 0);
        B[i] = (i < m && opt[i] == typ2) ? cd(1, 0) : cd(0, 0);
    }
    dft();
}

set<ull> st;

int main()
{
    int case_id = 0;
    for (int i = pow_magic[0] = 1; i < MAX_N; i++)
        pow_magic[i] = pow_magic[i - 1] * bitnum;
    while (scanf("%d", &k) && k != -1)
    {
        memset(res, 0, sizeof(res)), scanf("%s%s", str, opt);
        n = strlen(str), m = strlen(opt), poly_bit = 0;
        printf("Case %d: ", ++case_id);
        if (n < m)
        {
            puts("0");
            continue;
        }
        for (int i = 0; i < (m >> 1); i++)
            swap(opt[i], opt[m - i - 1]);
        // printf("%s\n", opt);
        while ((1 << poly_bit) < (2 * max(n, m) + 2))
            poly_bit++;
        poly_len = (1 << poly_bit);
        fft_initialize();
        build('a', 'b'), build('b', 'a');
        prefix[0] = 0, st.clear();
        int ans = 0;
        for (int i = 0; i < n; i++)
            prefix[i + 1] = prefix[i] * bitnum + (str[i] - 'a' + 1);
        for (int i = m - 1; i < n; i++)
        {
            ull now = prefix[i + 1] - prefix[i - m + 1] * pow_magic[m];
            if (st.count(now))
                continue;
            else if (res[i] <= k)
                ans++, st.insert(now);
        }
        printf("%d\n", ans);
    }
    return 0;
}