// P1377.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int seq[MAX_N], pos[MAX_N], lft[MAX_N], rig[MAX_N], n, lson[MAX_N], rson[MAX_N];

void dfs(int u)
{
    if (u == 0)
        return;
    printf("%d ", u);
    dfs(lson[u]), dfs(rson[u]);
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &seq[i]), pos[seq[i]] = i;
        lft[i] = i - 1, rig[i] = i + 1;
    }
    for (int i = n; i >= 2; i--)
    {
        //  connect to the prev or back one;
        int l = lft[seq[i]], r = rig[seq[i]];
        if (pos[l] > pos[r])
            rson[l] = seq[i];
        else
            lson[r] = seq[i];
        lft[r] = l, rig[l] = r;
    }
    dfs(seq[1]);
    return 0;
}