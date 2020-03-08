// CF1322A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

int n, pre[MAX_N];
char str[MAX_N];

int main()
{
    scanf("%d%s", &n, str + 1);
    int acc = 0, l = 0, r = 0;
    for (int i = 1; i <= n; i++)
        l += str[i] == '(', r += str[i] == ')', pre[i] = pre[i - 1] + ((str[i] == ')') ? -1 : 1);
    if (l != r)
        return puts("-1"), 0;
    int last_negative = -1, ans = 0;
    for (int i = 1; i <= n; i++)
    {
        if (pre[i] < 0 && last_negative == -1)
            last_negative = i;
        if (pre[i] == 0 && last_negative != -1)
            ans += i - last_negative + 1, last_negative = -1;
    }
    printf("%d\n", ans);
    return 0;
}