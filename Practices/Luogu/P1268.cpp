// P1268.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 33;

int n, matrix[MAX_N][MAX_N];

int main()
{
    while (scanf("%d", &n) && n != 0)
    {
        for (int i = 1; i <= n; i++)
            for (int j = i + 1; j <= n; j++)
                scanf("%d", &matrix[i][j]), matrix[j][i] = matrix[i][j];
        ll ans = matrix[1][2];
        for (int i = 3; i <= n; i++)
        {
            ll pans = 0x3f3f3f3f3f3f3f3f;
            for (int k = 2; k <= i - 1; k++)
                pans = min(pans, 1LL * (matrix[1][i] + matrix[i][k] - matrix[k][1]) >> 1);
            ans += pans;
        }
        printf("%lld\n", ans);
    }
    return 0;
}