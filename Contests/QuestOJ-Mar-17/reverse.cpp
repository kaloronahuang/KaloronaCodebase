// reverse.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e7 + 5, MAX_R = MAX_N << 2;

int n, *match, lb, rb, cnt;
char org[2][MAX_N], str[MAX_R];

int getId(int x) { return ((x - 1) >> 1) + 1; }

int main()
{
    scanf("%d%s%s", &n, org[0] + 1, org[1] + 1);
    lb = 1, rb = n;
    while (org[0][lb] == org[1][lb] && lb < n)
        lb++;
    while (org[0][rb] == org[1][rb] && rb > 1)
        rb--;
    bool flag = lb <= rb;
    // find the palindromes which get cross that;
    // save some fucking memory to generate the smaller str;
    if (flag)
    {
        str[0] = '!', str[++cnt] = '#';
        for (int i = 1; i <= n; i++)
            str[++cnt] = org[0][i], str[++cnt] = '#', str[++cnt] = org[1][i], str[++cnt] = '#';
        str[++cnt] = '?';
    }
    else
    {
        str[0] = '!', str[++cnt] = '#';
        for (int i = 1; i <= n; i++)
            str[++cnt] = org[0][i], str[++cnt] = '#';
        str[++cnt] = '?';
    }
    match = new int[cnt + 5], memset(match, 0, sizeof(int) * (cnt + 5));
    int matchpoint = 0, rig = 0;
    long long ans = 0;
    for (int i = 1; i <= cnt; i++)
    {
        if (i < rig)
            match[i] = min(rig - i, match[(matchpoint << 1) - i]);
        else
            match[i] = 1;
        while (str[i - match[i]] == str[i + match[i]])
            match[i]++;
        if (i + match[i] > rig)
            rig = i + match[i], matchpoint = i;
        if (flag && i % 2 == 1)
        {
            int pos = ((i - 1) >> 1) + 1, lpos = getId(pos - ((match[i] - 1) >> 1) + 1), rpos = getId(pos + ((match[i] - 1) >> 1) - 1);
            ans += max(0, min(lb - lpos + 1, rpos - rb + 1));
        }
        else if (!flag)
        {
            int pos = i;
            ans += match[i] >> 1;
        }
    }
    printf("%lld\n", ans);
    return 0;
}