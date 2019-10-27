// P3615.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 200100;

ll n, m, ki[MAX_N], prefix[MAX_N], mx_prefix[MAX_N], acc, ans;
char str[MAX_N];

int main()
{
    scanf("%lld%lld", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%s%lld", str + 1, &ki[i]);
        int len = strlen(str + 1);
        for (int j = len; j >= 1; j--)
            prefix[i] += (str[j] == 'F' ? -1 : 1), mx_prefix[i] = max(mx_prefix[i], prefix[i]);
        acc += prefix[i] * ki[i];
    }
    if (acc > 0)
        printf("-1"), exit(0);
    ans = 1, acc = 0;
    for (int i = m; i >= 1; i--)
    {
        if (prefix[i] > 0)
            ans = max(ans, acc + (ki[i] - 1) * prefix[i] + mx_prefix[i]);
        else
            ans = max(ans, acc + mx_prefix[i]);
        acc += prefix[i] * ki[i];
    }
    printf("%lld", ans - 1);
    return 0;
}