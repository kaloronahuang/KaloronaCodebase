// POJ1737.cpp
//#include <bits/stdc++.h>
#include <iostream>
#include <cstdio>
#define ll long long
using namespace std;
const int MAX_N = 60;
ll f[MAX_N], C[MAX_N][MAX_N], tmp;
int main()
{
    C[1][0] = C[1][1] = 1;
    for (int i = 2; i < MAX_N; i++)
    {
        C[i][0] = 1;
        for (int j = 1; j < MAX_N; j++)
            C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
    }
    f[1] = 1;
    for (int i = 2; i < MAX_N; i++)
    {
        f[i] = (1 << ((i * (i - 1)) >> 1));
        for (int j = 1; j < i; j++)
            f[i] -= f[j] * C[i - 1][j - 1] * (1 << (((i - j) * (i - j - 1)) >> 1));
    }
    while (~scanf("%d", &tmp) && tmp != 0)
        printf("%lld\n", f[tmp]);
    return 0;
}