// POJ1952.cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int MAX_N = 5050;
int arr[MAX_N], n, dp[MAX_N], f[MAX_N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &arr[i]), dp[i] = f[i] = 1;
    arr[0] = 0x3f3f3f3f;
    for (int i = 2; i <= n; i++)
        for (int j = i - 1; j >= 1; j--)
        {
            if (arr[j] > arr[i])
            {
                if (dp[j] >= dp[i])
                    dp[i] = dp[j] + 1, f[i] = f[j];
                else if (dp[i] == dp[j] + 1)
                    f[i] += f[j];
            }
            else if (arr[j] == arr[i])
            {
                if (dp[i] == 1)
                    f[i] = 0;
                break;
            }
        }
    int ans1 = 0, ans2 = 0;
    for (int i = n; i >= 1; i--)
        ans1 = max(ans1, dp[i]);
    for (int i = n; i >= 1; i--)
        if (dp[i] == ans1)
            ans2 += f[i];
    printf("%d %d", ans1, ans2);
    return 0;
}