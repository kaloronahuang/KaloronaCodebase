// C.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 2e5 + 200;

int n, q, ai[MAX_N];
ll sum;

int main()
{
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    for (int i = 2; i <= n; i++)
        sum += max(0, max(ai[i - 1], ai[i]));
    while (q--)
    {
        int p, x;
        scanf("%d%d", &p, &x);
        if (p > 1)
            sum = sum - max(0, max(ai[p], ai[p - 1])) + max(0, max(x, ai[p - 1]));
        if (p < n)
            sum = sum - max(0, max(ai[p], ai[p + 1])) + max(0, max(x, ai[p + 1]));
        ai[p] = x;
        printf("%lld\n", sum);
    }
    return 0;
}