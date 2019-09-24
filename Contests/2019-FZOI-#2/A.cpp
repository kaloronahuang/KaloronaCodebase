// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 20;

int n, ki[MAX_N], pre[MAX_N], ans;

void dfs(int pos, int closed)
{
    if (pos == 0)
        return (void)(ans++);
    for (int i = closed; i <= n; i++)
        if (ki[i] > 0)
        {
            ki[i]--;
            if (pre[i] == ki[i] + 1)
                dfs(pos - 1, closed - 1);
            else
                dfs(pos - 1, closed);
            ki[i]++;
        }
}

int main()
{
    int tot = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ki[i]), tot += ki[i], pre[i] = ki[i];
    dfs(tot - 1, n);
    printf("%d", ans);
    return 0;
}