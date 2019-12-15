// P4555.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int n, cnt, ll[MAX_N], rr[MAX_N], pi[MAX_N], r, mid;
char org[MAX_N], str[MAX_N];

int main()
{
    scanf("%s", org + 1), n = strlen(org + 1);
    str[++cnt] = '?', str[++cnt] = '#';
    for (int i = 1; i <= n; i++)
        str[++cnt] = org[i], str[++cnt] = '#';
    str[++cnt] = '!';
    for (int i = 1; i <= cnt; i++)
    {
        if (i <= r)
            pi[i] = min(pi[(mid << 1) - i], r - i + 1);
        else
            pi[i] = 1;
        while (str[i - pi[i]] == str[i + pi[i]])
            pi[i]++;
        if (i + pi[i] > r)
            mid = i, r = i + pi[i] - 1;
        ll[i + pi[i] - 1] = max(ll[i + pi[i] - 1], pi[i] - 1);
        rr[i - pi[i] + 1] = max(rr[i - pi[i] + 1], pi[i] - 1);
    }
    for (int i = 2; i <= cnt; i += 2)
        rr[i] = max(rr[i], rr[i - 2] - 2);
    for (int i = 2; i <= cnt; i += 2)
        ll[i] = max(ll[i], ll[i + 2] - 2);
    int ans = 0;
    for (int i = 2; i <= cnt; i += 2)
        if (ll[i] && rr[i])
            ans = max(ans, ll[i] + rr[i]);
    printf("%d\n", ans);
    return 0;
}