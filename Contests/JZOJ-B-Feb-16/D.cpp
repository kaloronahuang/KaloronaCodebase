// D.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 1000010;
int n, d, info[MAX_N][6], st[10], ans;
void calc(int stat)
{
    int mn = (1 << 29), mx = -mn;
    for (int i = 1; i <= d; i++, stat >>= 1)
        st[i] = stat & 1;
    for (int i = 1; i <= n; i++)
    {
        int acc = 0;
        for (int j = 1; j <= d; j++)
            acc += (st[j] == 1) ? info[i][j] : -info[i][j];
        if (acc != 0)
            mn = min(mn, acc), mx = max(mx, acc);
    }
    ans = max(mx - mn, ans);
}
int main()
{
    scanf("%d%d", &n, &d);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= d; j++)
            scanf("%d", &info[i][j]);
    for (int i = 0; i < (1 << d); i++)
        calc(i);
    printf("%d", ans);
    return 0;
}