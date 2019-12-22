// YBT-OJ1684.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 25;

int T, n, seq[MAX_N];

bool dfs(int dep, int last)
{
    int Astar = 0;
    for (int i = 1; i < n; i++)
        if (abs(seq[i] - seq[i + 1]) > 1)
            Astar++;
    if (Astar > dep)
        return false;
    bool tag = true;
    for (int i = 1; i < n; i++)
        tag &= (seq[i] + 1 == seq[i + 1]);
    if (tag)
        return true;
    if (dep == 0)
        return false;
    for (int i = 1; i <= n; i++)
        if (i != last)
        {
            reverse(seq + 1, seq + 1 + i);
            if (dfs(dep - 1, i))
                return true;
            reverse(seq + 1, seq + 1 + i);
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
            scanf("%d", &seq[i]);
        for (int dep = 0; dep <= (n - 1) * 2; dep++)
            if (dfs(dep, 0))
            {
                printf("%d\n", dep);
                break;
            }
    }
    return 0;
}