// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 110;

int n, li[MAX_N], ri[MAX_N], max_sum;
bitset<MAX_N * MAX_N * MAX_N> pre, now, zero;

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &li[i], &ri[i]), max_sum += ri[i] * ri[i];
    pre[0] = true;
    for (int i = 1; i <= n; i++)
    {
        for (int j = li[i]; j <= ri[i]; j++)
            now |= (pre << (j * j));
        pre = now, now = zero;
    }
    printf("%lld\n", pre.count());
    return 0;
}