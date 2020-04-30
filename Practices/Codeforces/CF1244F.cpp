// CF1244F.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int n, k, lft[MAX_N], rig[MAX_N], dist[MAX_N];
char str[MAX_N];

int main()
{
    memset(dist, -1, sizeof(dist));
    scanf("%d%d%s", &n, &k, str + 1);
    for (int i = 1; i <= n; i++)
        lft[i] = i - 1, rig[i] = i + 1;
    lft[1] = n, rig[n] = 1;
    // bfs;
    queue<int> q;
    for (int i = 1; i <= n; i++)
        if (str[i] == str[lft[i]] || str[i] == str[rig[i]])
            // stable pt;
            q.push(i), dist[i] = 0;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        // lft & rig;
        if (dist[lft[u]] == -1)
            dist[lft[u]] = dist[u] + 1, q.push(lft[u]);
        if (dist[rig[u]] == -1)
            dist[rig[u]] = dist[u] + 1, q.push(rig[u]);
    }
    for (int i = 1; i <= n; i++)
        if (dist[i] > k || dist[i] == -1)
            printf("%c", str[i] ^ ((k & 1) * ('W' ^ 'B')));
        else
            printf("%c", str[i] ^ ((dist[i] & 1) * ('W' ^ 'B')));
    return 0;
}