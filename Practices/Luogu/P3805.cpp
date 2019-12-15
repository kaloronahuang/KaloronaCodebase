// P3805.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 22000000;

int n, cnt, pi[MAX_N], ans;
char org[MAX_N], str[MAX_N];

int main()
{
    scanf("%s", org + 1), n = strlen(org + 1);
    // start to initialize;
    str[++cnt] = '?', str[++cnt] = '#';
    for (int i = 1; i <= n; i++)
        str[++cnt] = org[i], str[++cnt] = '#';
    str[++cnt] = '!';
    // do manacher;
    int mid = 0, r = 0;
    for (int i = 2; i <= cnt - 1; i++)
    {
        if (i <= r)
            pi[i] = min(pi[mid * 2 - i], r - i + 1);
        else
            pi[i] = 1;
        while (str[i - pi[i]] == str[i + pi[i]])
            pi[i]++;
        if (i + pi[i] > r)
            mid = i, r = i + pi[i] - 1;
        ans = max(ans, pi[i]);
    }
    printf("%d\n", ans - 1);
    return 0;
}