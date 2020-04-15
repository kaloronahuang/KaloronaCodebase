// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 33;

int T, n, ai[MAX_N], ci[MAX_N], tmp[MAX_N], tot;

bool dfs(int pos, int exp_swap, int curt)
{
    if (curt > exp_swap)
        return false;
    while (ci[pos] == pos && pos)
        pos--;
    if (pos == 0)
        return true;
    int fx = 0;
    for (int i = 2; i <= pos + 1; i++)
        fx += abs(ci[i] - ci[i - 1]) != 1;
    if (fx + curt > exp_swap)
        return false;
    for (int split = 2; split <= pos; split++)
    {
        for (int i = 1; i <= split; i++)
            tmp[i] = ci[split - i + 1];
        for (int i = 1; i <= split; i++)
            ci[i] = tmp[i];
        if (dfs(pos, exp_swap, curt + 1))
            return true;
        for (int i = 1; i <= split; i++)
            tmp[i] = ci[split - i + 1];
        for (int i = 1; i <= split; i++)
            ci[i] = tmp[i];
    }
    return false;
}

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            scanf("%d", &ai[i]), ci[i] = ai[i];
        tot = n;
        while (tot && ai[tot] == tot)
            tot--;
        for (int i = 0; i <= ((n - 1) << 1); i++)
            if (dfs(tot, i, 0))
            {
                printf("%d\n", i);
                break;
            }
    }
    return 0;
}