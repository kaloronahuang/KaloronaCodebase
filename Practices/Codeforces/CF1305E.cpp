// CF1305E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5050;

int n, m, ai[MAX_N], pos;

int main()
{
    scanf("%d%d", &n, &m);
    for (pos = 1; pos <= n; pos++)
        if (m - ((pos - 1) >> 1) >= 0)
            ai[pos] = pos, m -= (pos - 1) >> 1;
        else
            break;
    if (pos == n + 1 && m > 0)
        puts("-1"), exit(0);
    else if (pos <= n && m >= 0)
        ai[pos] = (pos << 1) - 1 - (m << 1);
    for (int i = 1; i <= min(n, pos); i++)
        printf("%d ", ai[i]);
    for (int i = pos + 1; i <= n; i++)
        printf("%d ", int(1e8 + 1e4 * (i - pos - 1)));
    puts("");
    return 0;
}