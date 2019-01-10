// P3773.cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int MAX_N = 233393, mod = 1000000007;
int n, arr[MAX_N], bucket[MAX_N], f[MAX_N], ans;
int getMod(int num) { return num >= mod ? num - mod : num; }
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &arr[i]), bucket[arr[i]] = i;
    for (int i = n; i >= 1; i--)
    {
        f[i] = 1;
        for (int j = (arr[i] & (arr[i] - 1)); j; j = arr[i] & (j - 1))
            if (bucket[j] > i)
                f[i] = getMod(f[i] + f[bucket[j]]);
        ans = getMod(ans + f[i]);
    }
    ans = (ans - n + mod) % mod;
    printf("%d", ans);
    return 0;
}