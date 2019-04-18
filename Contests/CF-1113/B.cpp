// B.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 3e5 + 20000;
int n, arr[MAX_N], sum[MAX_N];
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &arr[i]);
    sort(arr + 1, arr + 1 + n);
    for (int i = 1; i <= n; i++)
        sum[i] = sum[i - 1] + arr[i];
    int ans = sum[n];
    for (int i = n; i >= 2; i--)
        for (int j = 2; j <= arr[i]; j++)
            if (arr[i] % j == 0)
            {
                ans = min(ans, (sum[i - 1] - arr[1]) + arr[1] * j + arr[i] / j + sum[n] - sum[i]);
            }
    printf("%d", ans);
    return 0;
}