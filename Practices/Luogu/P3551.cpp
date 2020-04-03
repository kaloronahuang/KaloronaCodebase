// P3551.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

int n, k, pre[MAX_N], stk[MAX_N], tail, ans[MAX_N], anstot;
char str[MAX_N];

int main()
{
    scanf("%d%d%s", &n, &k, str + 1), k++;
    for (int i = 1; i <= n; i++)
    {
        stk[++tail] = i, pre[tail] = pre[tail - 1] + (str[i] == 'c');
        if (tail >= k && pre[tail] - pre[tail - k] == 1)
        {
            int cnt = k;
            while (cnt)
                ans[++anstot] = stk[tail--], cnt--;
        }
    }
    for (int i = anstot; i >= 1; i--)
    {
        printf("%d ", ans[i]);
        if (i % k == 1)
            puts("");
    }
    return 0;
}