// P1622.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 110;
int p, q, arr[MAX_N], f[MAX_N][MAX_N];
int main()
{
    scanf("%d%d", &p, &q);
    for (int i = 1; i <= q; i++)
        scanf("%d", &arr[i]);
    sort(arr + 1, arr + 1 + q);
    arr[0] = 0, arr[q + 1] = p + 1;
    for (int len = 1; len <= q; len++)
        for (int i = 1; i + len - 1 <= q; i++)
        {
            int j = i + len - 1;
            f[i][j] = 0x3f3f3f3f;
            for (int k = i; k <= j; k++)
                f[i][j] = min(f[i][j], f[i][k - 1] + f[k + 1][j] + arr[j + 1] - arr[i - 1] - 1 - 1);
        }
    printf("%d", f[1][q]);
    return 0;
}