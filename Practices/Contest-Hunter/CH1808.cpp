// CH1808.cpp
#include <bits/stdc++.h>
#define ull unsigned long long

using namespace std;

const int MAX_N = 1e5 + 200, base = 13331;

int nxt[MAX_N], n, m;
ull str[MAX_N];
char org[MAX_N][80];

int get_nxt(int len)
{
    for (int i = 2, j = 0; i <= len; i++)
    {
        while (j && str[j + 1] != str[i])
            j = nxt[j];
        if (str[j + 1] == str[i])
            j++;
        nxt[i] = j;
    }
    return len - nxt[len];
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%s", org[i] + 1);
        for (int j = 1; j <= m; j++)
            str[i] = int(org[i][j] - 'A') + str[i] * base;
    }
    int ans1 = get_nxt(n);
    memset(str, 0, sizeof(str));
    for (int j = 1; j <= m; j++)
        for (int i = 1; i <= n; i++)
            str[j] = int(org[i][j] - 'A') + str[j] * base;
    int ans = get_nxt(m) * ans1;
    printf("%d", ans);
    return 0;
}