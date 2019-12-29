// D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e6 + 200;

int nodes[MAX_N][3], last[MAX_N], ans[MAX_N], ptot = 1, n, m;
char opt[MAX_N];

void insert(char *str, int idx)
{
    int p = 1;
    for (int i = 1; str[i] != '\0'; i++)
    {
        int bit = str[i] - 'a';
        if (nodes[p][bit] == 0)
            nodes[p][bit] = ++ptot;
        p = nodes[p][bit];
        ans[p] = max(ans[p], idx - last[p] - 1), last[p] = idx;
    }
}

int walk(char *str)
{
    int p = 1;
    for (int i = 1; str[i] != '\0'; i++)
        p = nodes[p][str[i] - 'a'];
    return p;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%s", opt + 1), insert(opt, i);
    for (int i = 1, p; i <= m; i++)
    {
        scanf("%s", opt + 1), p = walk(opt);
        printf("%d\n", max(ans[p], n - last[p]));
    }
    return 0;
}