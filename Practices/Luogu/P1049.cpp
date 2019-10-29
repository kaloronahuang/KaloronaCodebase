// P1049.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 20100;

int seq[MAX_N], n, V;
bool dp[MAX_N];

int main()
{
    dp[0] = true;
    scanf("%d%d", &V, &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &seq[i]);
    for (int i = 1; i <= n; i++)
        for (int j = V; j >= seq[i]; j--)
            dp[j] |= dp[j - seq[i]];
    for (int i = V; i >= 0; i--)
        if (dp[i])
            printf("%d\n", V - i), exit(0);
    return 0;
}