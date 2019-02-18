// P1108.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 5050;
int n, arr[MAX_N], f[MAX_N], g[MAX_N], tot;
bool cmp(int a, int b) { return a > b; }
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &arr[i]);
    for (int i = 1; i <= n; i++)
    {
        f[i] = 1;
        for (int j = 1; j < i; j++)
            if (arr[j] > arr[i])
                f[i] = max(f[j] + 1, f[i]);
        tot = max(tot, f[i]);
    }
    for (int i = 1; i <= n; i++)
    {
        if (f[i] == 1)
            g[i] = 1;
        for (int j = 1; j < i; j++)
        {
            if (f[i] == f[j] && arr[i] == arr[j])
                g[j] = 0;
            if (f[i] == f[j] + 1 && arr[j] > arr[i])
                g[i] += g[j];
        }
    }
    long long ans = 0;
    for (int i = 1; i <= n; i++)
        if (f[i] == tot)
            ans += g[i];
    printf("%d %lld", tot, ans);
    return 0;
}