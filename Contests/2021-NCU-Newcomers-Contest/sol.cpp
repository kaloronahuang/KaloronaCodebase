// sol.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 110;

int T, n, ai[MAX_N];
bool ans;

void dfs(int u, int sum1, int sum2)
{
    if (ans)
        return;
    if (u == n + 1)
    {
        ans |= (sum1 == sum2);
        return;
    }
    if (ai[u] % 3 == 0)
    {
        dfs(u + 1, sum1 + ai[u], sum2);
    }
    else if (ai[u] % 7 == 0)
    {
        dfs(u + 1, sum1, sum2 + ai[u]);
    }
    else
    {
        dfs(u + 1, sum1 + ai[u], sum2);
        dfs(u + 1, sum1, sum2 + ai[u]);
    }
}

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n), ans = false;
        for (int i = 1; i <= n; i++)
            scanf("%d", &ai[i]);
        dfs(1, 0, 0);
        if (ans)
            puts("YES");
        else
            puts("NO");
    }
    return 0;
}