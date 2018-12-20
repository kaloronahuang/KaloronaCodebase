// CH5201.cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int N, M, dp[10020], arr[120];
int main()
{
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= N; i++)
        scanf("%d", &arr[i]);
    dp[0] = 1;
    for (int i = 1; i <= N; i++)
        for (int j = M; j >= arr[i]; j--)
            dp[j] += dp[j - arr[i]];
    printf("%d", dp[M]);
    return 0;
}