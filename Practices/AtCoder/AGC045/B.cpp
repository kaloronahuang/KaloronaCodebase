// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

int n, pre[MAX_N], suf[MAX_N], ans = 0x7fffffff;
char str[MAX_N];

void prepare()
{
    for (int i = 1; i <= n; i++)
        pre[i] = pre[i - 1] + (str[i] == '0' ? -1 : 1);
    suf[n + 1] = MAX_N;
    for (int i = n; i >= 0; i--)
        suf[i] = min(suf[i + 1], pre[i]);
}

void solve(int lbound)
{
    int bias = 0, upper = 0;
    for (int i = 1; i <= n; i++)
    {
        if (str[i] == '?' && suf[i] - 2 - bias >= lbound)
            bias += 2;
        pre[i] -= bias, upper = max(upper, pre[i]);
    }
    ans = min(ans, upper - lbound);
}

int main()
{
    scanf("%s", str + 1), n = strlen(str + 1);
    prepare(), solve(suf[0]);
    prepare(), solve(suf[0] - 1);
    printf("%d\n", ans);
    return 0;
}