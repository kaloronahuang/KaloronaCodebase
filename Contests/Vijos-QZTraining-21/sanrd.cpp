// sanrd.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int n, seq[MAX_N], pre[MAX_N], suf[MAX_N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &seq[i]);
    int p1 = 0, p2 = 0;
    for (int i = 1; i <= n; i++)
        if (seq[i] == 2)
            pre[i] = max(pre[p2] + 1, pre[p1] + 1), p2 = i;
        else
            pre[i] = pre[p1] + 1, p1 = i;
    p1 = n + 1, p2 = n + 1;
    for (int i = n; i >= 1; i--)
        if (seq[i] == 1)
            suf[i] = max(suf[p2] + 1, suf[p1] + 1), p1 = i;
        else
            suf[i] = suf[p2] + 1, p2 = i;
    int ans = 0;
    for (int i = 1; i < n; i++)
        ans = max(ans, pre[i] + suf[i + 1]);
    printf("%d", ans);
    return 0;
}