// CF1187C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1010;

int n, m, seq[MAX_N], li[MAX_N], ri[MAX_N], mark[MAX_N], qtot, prefix[MAX_N];

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1, opt, x, y; i <= m; i++)
    {
        scanf("%d%d%d", &opt, &x, &y);
        if (opt == 1)
            mark[x]++, mark[y]--;
        else
            li[++qtot] = x, ri[qtot] = y;
    }
    for (int i = 1; i < n; i++)
        mark[i] += mark[i - 1];
    for (int i = 1; i < n; i++)
        mark[i] = mark[i] > 0, prefix[i] = prefix[i - 1] + mark[i];
    for (int i = 1; i <= qtot; i++)
        // must be more;
        if (prefix[ri[i] - 1] - prefix[li[i] - 1] == ri[i] - li[i])
            puts("NO"), exit(0);
    puts("YES");
    for (int i = 1, pre = n + 2; i <= n; i++)
        printf("%d ", mark[i - 1] ? pre : --pre);
    return 0;
}