// P1528.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = (1 << 10) + 200;

int n, m, cakes[MAX_N], inp[MAX_N], sum, waste_already, prefix[MAX_N], tmp[MAX_N], mid;

bool dfs(int u, int last)
{
    if (u == 0)
        return true;
    if (sum - waste_already < prefix[mid])
        return false;
    for (int i = last; i <= n; i++)
        if (tmp[i] >= inp[u])
        {
            tmp[i] -= inp[u];
            if (tmp[i] < inp[1])
                waste_already += tmp[i];
            if (inp[u] == inp[u - 1])
            {
                if (dfs(u - 1, i))
                    return true;
            }
            else if (dfs(u - 1, 1))
                return true;
            if (tmp[i] < inp[1])
                waste_already -= tmp[i];
            tmp[i] += inp[u];
        }
    return false;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &cakes[i]), sum += cakes[i];
    scanf("%d", &m);
    for (int i = 1; i <= m; i++)
        scanf("%d", &inp[i]);
    sort(inp + 1, inp + 1 + m);
    while (sum < inp[m])
        m--;
    for (int i = 1; i <= m; i++)
        prefix[i] = prefix[i - 1] + inp[i];
    int l = 0, r = m, ans;
    while (l <= r)
    {
        mid = (l + r) >> 1, waste_already = 0;
        for (int i = 1; i <= n; i++)
            tmp[i] = cakes[i];
        if (dfs(mid, 1))
            l = mid + 1, ans = mid;
        else
            r = mid - 1;
    }
    printf("%d", ans);
    return 0;
}