// P3175.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 22, MAX_M = (1 << MAX_N);
const double eps = 1e-8;

int n, poly_siz;
double pi[MAX_M];

void fwt_or(double *arr, int opt)
{
    for (int step = 1; step < poly_siz; step <<= 1)
        for (int j = 0; j < poly_siz; j += (step << 1))
            for (int k = j; k < j + step; k++)
                arr[k + step] += opt * arr[k];
}

int main()
{
    scanf("%d", &n), poly_siz = (1 << n);
    for (int i = 0; i < poly_siz; i++)
        scanf("%lf", &pi[i]);
    fwt_or(pi, 1);
    double ans = 0;
    for (int i = 1; i < poly_siz; i++)
    {
        if (1 - pi[(poly_siz - 1) ^ i] < eps)
            return puts("INF"), 0;
        ans += 1 / (1 - pi[(poly_siz - 1) ^ i]) * ((__builtin_popcount(i) & 1) ? 1 : -1);
    }
    printf("%.9lf\n", ans);
    return 0;
}