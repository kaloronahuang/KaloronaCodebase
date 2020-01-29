// CF734F.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 201000;

typedef long long ll;

int n, bi[MAX_N], ci[MAX_N], bit[32];
ll ai[MAX_N], acnt, b_exp[MAX_N], c_exp[MAX_N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &bi[i]);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ci[i]);
    for (int i = 1; i <= n; i++)
        ai[i] = (0LL + bi[i] + ci[i]), acnt += ai[i];
    if (acnt % (2 * n) != 0)
        puts("-1"), exit(0);
    acnt /= 2 * n;
    for (int i = 1; i <= n; i++)
    {
        ai[i] -= acnt;
        if (ai[i] < 0 || ai[i] % n != 0)
            puts("-1"), exit(0);
        ai[i] /= n;
    }
    for (int b = 0; b <= 30; b++)
        for (int i = 1; i <= n; i++)
            bit[b] += ((ai[i] >> b) & 1);
    for (int i = 1; i <= n; i++)
        for (int b = 0; b <= 30; b++)
            if (ai[i] & (1 << b))
            {
                b_exp[i] += 1LL * bit[b] * (1 << b);
                c_exp[i] += 1LL * n * (1 << b);
            }
            else
                c_exp[i] += 1LL * bit[b] * (1 << b);
    for (int i = 1; i <= n; i++)
        if (bi[i] != b_exp[i] || ci[i] != c_exp[i])
            puts("-1"), exit(0);
    for (int i = 1; i <= n; i++)
        printf("%lld ", ai[i]);
    puts("");
    return 0;
}