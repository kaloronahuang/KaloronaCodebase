// BZ3451.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 300100;
const double pi = acos(-1.0);

typedef complex<double> cd;

int n, head[MAX_N], current, rev[MAX_N], poly_bit, poly_siz, siz[MAX_N], len, ansBox[MAX_N];
bool tag[MAX_N];
cd A[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void fft_prepare()
{
    poly_bit = 0, poly_siz = 1;
    while ((1 << poly_bit) <= len)
        poly_bit++, poly_siz <<= 1;
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
                arr[k + step] = arr[k] - t, arr[k] += t;
            }
        }
    }
    if (dft == -1)
        for (int i = 0; i < poly_siz; i++)
            arr[i] /= poly_siz;
}

int root, val;

void findRoot(int u, int fa, int capacity)
{
    int max_size = 0;
    siz[u] = 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa && !tag[edges[i].to])
        {
            findRoot(edges[i].to, u, capacity);
            max_size = max(max_size, siz[edges[i].to]), siz[u] += siz[edges[i].to];
        }
    if (max(max_size, capacity - siz[u]) < val)
        val = max(max_size, capacity - siz[u]), root = u;
}

int findRoot(int entryPoint, int capacity) { return root = 0, val = 0x3f3f3f3f, findRoot(entryPoint, 0, capacity), root; }

void collect(int u, int fa, int dep)
{
    A[dep] += 1, len = max(len, dep);
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa && !tag[edges[i].to])
            collect(edges[i].to, u, dep + 1);
}

void solve(int u, int capacity)
{
    len = 0, tag[u] = true, collect(u, 0, 0);
    len <<= 1, fft_prepare(), fft_initialize();
    fft(A, 1);
    for (int i = 0; i < poly_siz; i++)
        A[i] *= A[i];
    fft(A, -1);
    for (int i = 0; i <= len; i++)
        ansBox[i] += int(A[i].real() + 0.5);
    for (int i = 0; i < poly_siz; i++)
        A[i] = 0;
    for (int i = head[u], tmp; i != -1; i = edges[i].nxt)
        if (!tag[edges[i].to])
        {
            len = 0, collect(edges[i].to, u, 1);
            len <<= 1, fft_prepare(), fft_initialize();
            fft(A, 1);
            for (int i = 0; i < poly_siz; i++)
                A[i] *= A[i];
            fft(A, -1);
            for (int i = 0; i <= len; i++)
                ansBox[i] -= int(A[i].real() + 0.5);
            for (int i = 0; i < poly_siz; i++)
                A[i] = 0;
            tmp = siz[edges[i].to], solve(findRoot(edges[i].to, tmp), tmp);
        }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1, u, v; i < n; i++)
        scanf("%d%d", &u, &v), u++, v++, addpath(u, v), addpath(v, u);
    solve(findRoot(1, n), n);
    double ans = 0;
    for (int i = 0; i < n; i++)
        ans += double(ansBox[i]) / double(i + 1);
    printf("%.4lf\n", ans);
    return 0;
}