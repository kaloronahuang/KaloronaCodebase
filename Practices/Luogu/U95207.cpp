// U95207.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, pre0[MAX_N], pre1[MAX_N], pre[MAX_N], ans = -0x3f3f3f3f;
char str[MAX_N];

int main()
{
    scanf("%s", str + 1), n = strlen(str + 1);
    for (int i = 1, mn = 0; i <= n; i++)
    {
        pre0[i] = pre0[i - 1] + (str[i] == '0');
        pre1[i] = pre1[i - 1] + (str[i] == '1');
        pre[i] = pre0[i] - pre1[i];
        ans = max(ans, pre[i] - mn);
        mn = min(mn, pre[i]);
    }
    printf("%d", ans);
    return 0;
}