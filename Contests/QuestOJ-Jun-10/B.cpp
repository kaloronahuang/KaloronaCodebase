// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2020;

int n, ai[MAX_N], m;
bitset<MAX_N * MAX_N> f;

int main()
{
    scanf("%d", &n), f[0] = 1;
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]), m += ai[i], f = f | (f << ai[i]);
    m = (m + 1) >> 1;
    for (int i = 1; i <= n * n; i++)
        if (i >= m && f[i])
            printf("%d\n", i), exit(0);
    return 0;
}