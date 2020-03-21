// ARC103A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1010;

int n, xi[MAX_N], yi[MAX_N], parity, m, segs[MAX_N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &xi[i], &yi[i]);
    parity = (xi[1] + yi[1]) & 1;
    for (int i = 2; i <= n; i++)
        if (((xi[i] + yi[i]) & 1) != parity)
            puts("-1"), exit(0);
    if (parity == 0)
        segs[++m] = 1;
    for (int i = 30; i >= 0; i--)
        segs[++m] = (1 << i);
    printf("%d\n", m);
    for (int i = 1; i <= m; i++)
        printf("%d ", segs[i]);
    puts("");
    for (int i = 1; i <= n; i++, puts(""))
        for (int j = 1; j <= m; j++)
            if (abs(xi[i]) > abs(yi[i]))
                if (xi[i] > 0)
                    xi[i] -= segs[j], putchar('R');
                else
                    xi[i] += segs[j], putchar('L');
            else if (yi[i] > 0)
                yi[i] -= segs[j], putchar('U');
            else
                yi[i] += segs[j], putchar('D');
    return 0;
}