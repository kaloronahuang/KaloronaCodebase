// CF1190C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, k, lft[MAX_N], rig[MAX_N];
char str[MAX_N];

int main()
{
    scanf("%d%d%s", &n, &k, str + 1);
    lft[1] = 1, rig[n] = n;
    for (int i = 2; i <= n; i++)
        lft[i] = (str[i] == str[i - 1]) ? lft[i - 1] : i;
    for (int i = n - 1; i >= 1; i--)
        rig[i] = (str[i] == str[i + 1]) ? rig[i + 1] : i;
    bool flag1 = (n == k || lft[n - k] == 1 || rig[k + 1] == n), flag2 = ((k << 1) >= n);
    for (int i = 2; i <= n - k; i++)
        if (str[i - 1] == str[i + k] && lft[i - 1] == 1 && rig[i + k] == n)
            flag1 |= true;
    for (int i = 2; i <= n - k; i++)
        if (lft[i - 1] != 1 || rig[i + k] != n)
            flag2 &= false;
    if (flag1)
        puts("tokitsukaze");
    else if (flag2)
        puts("quailty");
    else
        puts("once again");
    return 0;
}