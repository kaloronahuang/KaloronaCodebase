// P1901.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 1000100;

int hi[MAX_N], vi[MAX_N], n, sum[MAX_N], ans, stk[MAX_N], tail;

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", &hi[i], &vi[i]);
        while (tail > 0 && hi[stk[tail]] < hi[i])
            sum[i] += vi[stk[tail--]];
        sum[stk[tail]] += vi[i];
        stk[++tail] = i;
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
        ans = max(sum[i], ans);
    printf("%d", ans);
    return 0;
}