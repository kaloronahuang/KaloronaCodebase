// HDU-1465.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 30;

ll fac[MAX_N], C[MAX_N][MAX_N], f[MAX_N];
int n;

void preprocess()
{
    for (int i = fac[0] = 1; i < MAX_N; i++)
    {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; j++)
            C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
        fac[i] = fac[i - 1] * i;
    }
    for (int i = 2; i < MAX_N; i++)
        for (int j = 0; j <= i; j++)
            f[i] += (((i - j) & 1) ? -1 : 1) * C[i][j] * fac[j];
}

int main()
{
    preprocess();
    while (scanf("%d", &n) != EOF)
        printf("%lld\n", f[n]);
    return 0;
}

