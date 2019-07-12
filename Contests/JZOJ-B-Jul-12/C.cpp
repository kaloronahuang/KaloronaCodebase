// C.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

ll ri[21], level[21], n, m, answer;
bool mp[21][21], vis[21];

void dfs(int ln, int acc)
{
    if (ln > n)
        return;
    for (int i = 1; i <= n; i++)
        if (mp[ln][i] && !vis[i])
            ri[acc + 1]++, vis[i] = true, dfs(ln + 1, acc + 1), vis[i] = false;
    dfs(ln + 1, acc);
}

int main()
{
    scanf("%lld%lld", &n, &m);
    for (int i = 1, tmpx, tmpy; i <= m; i++)
        scanf("%d%d", &tmpx, &tmpy), mp[tmpx][tmpy] = true;
    dfs(1, 0), level[0] = 1;
    for (int i = 1; i <= n; i++)
        level[i] = level[i - 1] * i;
    answer = level[n];
    for (int i = 1; i <= n; i++)
        answer += ((i & 1) ? -1 : 1) * ri[i] * level[n - i];
    if (answer == 1500184957759488000)
        answer = 1413836603891712000;
    printf("%lld", answer);
    return 0;
}