// B.cpp
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int T, n, a, b;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d%d", &n, &a, &b);
        int a_pre = a - 1, b_pre = b - 1;
        a_pre -= min(a_pre, max(0, n - b - 1)), b_pre -= min(b_pre, max(0, n - a - 1));
        printf("%d ", max(a_pre, b_pre) + 1);
        a_pre = a - 1, b_pre = b - 1;
        int ans2 = min(a_pre, n - b) + min(b_pre, n - a);
        a_pre -= min(a_pre, n - b), b_pre -= min(b_pre, n - a);
        ans2 += min(a_pre, b_pre) + 1;
        printf("%d\n", min(ans2, n));
    }
    return 0;
}