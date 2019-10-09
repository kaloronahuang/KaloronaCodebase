// P1120.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 66;

int n, tot, seq[MAX_N], lbound, rbound, limit_length, st_tot;
bool vis[5000];

bool dfs(int idx, int now_len, int last_idx)
{
    if (idx > st_tot)
        return true;
    if (now_len == limit_length)
        return dfs(idx + 1, 0, 1);
    int fail = 0;
    for (int i = last_idx; i <= n; i++)
        if (!vis[i] && now_len + seq[i] <= limit_length && fail != seq[i])
        {
            vis[i] = true;
            if (dfs(idx, now_len + seq[i], i + 1))
                return true;
            fail = seq[i], vis[i] = false;
            if (now_len == 0 || now_len + seq[i] == limit_length)
                return false;
        }
    return false;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1, tmp; i <= n; i++)
    {
        scanf("%d", &tmp);
        if (tmp <= 50)
            seq[++tot] = tmp, lbound = max(lbound, tmp), rbound += tmp;
    }
    n = tot;
    sort(seq + 1, seq + 1 + n), reverse(seq + 1, seq + 1 + n);
    for (int i = lbound; i <= rbound; i++)
    {
        if (rbound % i != 0)
            continue;
        limit_length = i, st_tot = rbound / i;
        memset(vis, false, sizeof(vis));
        if (dfs(1, 0, 1))
            break;
    }
    printf("%d", limit_length);
    return 0;
}