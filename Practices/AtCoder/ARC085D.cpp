// ARC085D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2020;

int n, X, Y, ai[MAX_N], dp[MAX_N][2];

int main()
{
    scanf("%d%d%d", &n, &X, &Y);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    if (n == 1)
        printf("%d\n", abs(ai[1] - Y));
    else
        printf("%d\n", max(abs(ai[n - 1] - ai[n]), abs(ai[n] - Y)));
    return 0;
}