// yist.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2020;

int n;
char str[MAX_N], ans[MAX_N];

int main()
{
    scanf("%d%s", &n, str + 1);
    for (int i = 1; i <= (n >> 1); i++)
        ans[i] = str[n - 2 * i + 1];
    if (n % 2 == 0)
        for (int i = 1; i <= n - (n >> 1); i++)
            ans[i + (n >> 1)] = str[i << 1];
    else
        for (int i = 1; i <= n - (n >> 1); i++)
            ans[i + (n >> 1)] = str[(i << 1) - 1];
    for (int i = 1; i <= n; i++)
        printf("%c", ans[i]);
    return 0;
}