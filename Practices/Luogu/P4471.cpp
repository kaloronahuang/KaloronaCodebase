// P4471.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e6 + 200;

int n, nodes[MAX_N][26], ptot, tag[MAX_N], gans, f[MAX_N];
char str[MAX_N];

void insert(char *str)
{
    int p = 0;
    for (int i = 1; str[i] != '\0'; i++)
    {
        if (nodes[p][str[i] - 'a'] == 0)
            nodes[p][str[i] - 'a'] = ++ptot;
        p = nodes[p][str[i] - 'a'];
    }
    tag[p]++;
}

void dfs(int u, int fa)
{
    int max_val = 0, second_val = 0, cnt = 0;
    for (int i = 0; i < 26; i++)
        if (nodes[u][i])
        {
            dfs(nodes[u][i], u);
            if (tag[nodes[u][i]] == 0)
                continue;
            cnt += tag[nodes[u][i]];
            if (f[nodes[u][i]] >= max_val)
                swap(max_val, second_val), max_val = f[nodes[u][i]];
            else if (f[nodes[u][i]] > second_val)
                second_val = f[nodes[u][i]];
        }
    if (tag[u])
        f[u] = cnt + max_val;
    gans = max(gans, max_val + second_val + cnt + tag[u]);
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%s", str + 1), reverse(str + 1, str + 1 + strlen(str + 1)), insert(str);
    dfs(0, -1), printf("%d\n", gans);
    return 0;
}