// P2737.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 256 * 256 - 256;

int n, seq[20];
bool dp[MAX_N + 300];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &seq[i]);
    dp[0] = true;
    for (int i = 1; i <= n; i++)
        for (int j = seq[i]; j <= MAX_N; j++)
            dp[j] |= dp[j - seq[i]];
    for (int i = MAX_N; i >= 0; i--)
        if (dp[i] == false)
        {
            if (i >= 65279)
                puts("0");
            else
                printf("%d", i);
            exit(0);
        }
    printf("0");
    return 0;
}