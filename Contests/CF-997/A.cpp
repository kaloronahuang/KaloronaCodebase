// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e5 + 200;

int n, x, y, cnt;
char str[MAX_N];

int main()
{
    scanf("%d%d%d%s", &n, &x, &y, str + 1);
    str[0] = '1';
    for (int i = 1; i <= n; i++)
        cnt += (str[i] == '0' && str[i - 1] == '1');
    long long ans = 0;
    if (cnt == 0)
        ans = 0;
    else
        ans = 1LL * (cnt - 1) * min(x, y) + y;
    printf("%lld\n", ans);
    return 0;
}