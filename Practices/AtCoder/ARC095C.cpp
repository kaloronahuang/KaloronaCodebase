// ARC095C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 15;

int n, m, order[MAX_N], best_match, mpoint[MAX_N];
char mp[MAX_N][MAX_N], *lmp[MAX_N];

bool check(int pos)
{
    if (pos == m + 1)
        return true;
    if (mpoint[pos])
        return check(pos + 1);
    int cnt = 0;
    for (int i = pos; i <= m; i++)
        if (mpoint[i] == 0)
            cnt++;
    for (int i = pos; i <= m; i++)
        if (mpoint[i] == 0)
        {
            bool flag = true;
            for (int j = 1; j <= n; j++)
                flag &= (mp[j][i] == mp[order[j]][pos] && mp[order[j]][i] == mp[j][pos]);
            if (i == pos)
            {
                if (flag && (cnt & 1))
                {
                    mpoint[pos] = i;
                    if (check(pos + 1))
                        return true;
                    mpoint[pos] = 0;
                }
            }
            else if (flag)
            {
                mpoint[pos] = i, mpoint[i] = pos;
                if (check(pos + 1))
                    return true;
                mpoint[pos] = mpoint[i] = 0;
            }
        }
    return false;
}

bool dfs(int pos)
{
    if (pos == n + 1)
        return check(1);
    if (order[pos] != 0)
        return dfs(pos + 1);
    int cnt = 0;
    for (int i = pos; i <= n; i++)
        if (order[i] == 0)
            cnt++;
    for (int i = pos; i <= n; i++)
        if (order[i] == 0)
        {
            order[pos] = i, order[i] = pos;
            if (((cnt & 1) || (i != pos)) && dfs(pos + 1))
                return true;
            order[pos] = order[i] = 0;
        }
    return false;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%s", mp[i] + 1);
    if (dfs(1))
        puts("YES");
    else
        puts("NO");
    return 0;
}