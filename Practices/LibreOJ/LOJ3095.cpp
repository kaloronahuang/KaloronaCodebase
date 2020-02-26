// LOJ3095.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

int n, len[MAX_N], cnt;
char str[MAX_N];

void process(int pos)
{
    if (pos == cnt)
        return;
    bool flag = false;
    if (str[len[pos]] > str[len[pos + 1]])
        for (int i = len[pos]; i < len[pos + 1]; i++)
            printf("%d ", i);
    else
        flag = true;
    process(pos + 1);
    if (flag)
        for (int i = len[pos]; i < len[pos + 1]; i++)
            printf("%d ", i);
}

int main()
{
    scanf("%d%s", &n, str + 1);
    for (int i = 1; i <= n; i++)
    {
        if (str[i] == str[i - 1])
            continue;
        len[++cnt] = i;
    }
    len[++cnt] = n + 1, process(1);
    return 0;
}