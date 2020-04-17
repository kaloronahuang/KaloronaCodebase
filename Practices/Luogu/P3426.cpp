// P3426.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e5 + 200;

int n, link[MAX_N], last_pos[MAX_N], dp[MAX_N];
char str[MAX_N];

int main()
{
    scanf("%s", str + 1), n = strlen(str + 1);
    for (int i = 2, j = 0; i <= n; i++)
    {
        while (j && str[j + 1] != str[i])
            j = link[j];
        if (str[j + 1] == str[i])
            j++;
        link[i] = j;
    }
    dp[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        dp[i] = i;
        if (last_pos[dp[link[i]]] >= i - link[i])
            dp[i] = dp[link[i]];
        last_pos[dp[i]] = i;
    }
    printf("%d\n", dp[n]);
    return 0;
}