// POJ1722.cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int MAX_N = 110, DOM = 10000;

char dp[MAX_N][DOM << 2], op[MAX_N];
int arr[MAX_N], n, target;

int main()
{
    scanf("%d%d", &n, &target);
    for (int i = 1; i <= n; i++)
        scanf("%d", &arr[i]);
    target += DOM;
    memset(dp, 0, sizeof(dp));
    dp[2][arr[1] - arr[2] + DOM] = '-';
    for (int i = 2; i < n; i++)
        for (int j = 0; j < (DOM << 1); j++)
            if (dp[i][j] != 0)
            {
                if (j - arr[i + 1] >= 0)
                    dp[i + 1][j - arr[i + 1]] = '-';
                if (j + arr[i + 1] <= (DOM << 1))
                    dp[i + 1][j + arr[i + 1]] = '+';
            }
    for (int i = n; i >= 2; i--)
    {
        op[i] = dp[i][target];
        if (dp[i][target] == '+')
            target -= arr[i];
        else
            target += arr[i];
    }
    int cnt = 0;
    for (int i = 2; i <= n; i++)
        if (op[i] == '+')
        {
            printf("%d\n", i - cnt - 1);
            cnt++;
        }
    for (int i = 1; i <= n; i++)
        if (op[i] == '-')
            puts("1");
    return 0;
}