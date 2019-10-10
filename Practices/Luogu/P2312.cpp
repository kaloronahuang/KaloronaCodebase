// P2312.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200, mod = 1e9 + 7;

int n, m, ai[MAX_N], sol[MAX_N], tot;
char str[MAX_N];

int read()
{
    int x = 0, w = 1;
    char ch = 0;
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            w = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = (1LL * x * 10 + (ch - '0')) % mod;
        ch = getchar();
    }
    return x * w;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n + 1; i++)
        ai[i] = read();
    for (int i = 1; i <= m; i++)
    {
        // check;
        int ans = 0;
        for (int j = n + 1; j >= 1; j--)
            ans = (1LL * ans * i + 1LL * ai[j] + mod) % mod;
        if (ans == 0)
            sol[++tot] = i;
    }
    printf("%d\n", tot);
    for (int i = 1; i <= tot; i++)
        printf("%d\n", sol[i]);
    return 0;
}
