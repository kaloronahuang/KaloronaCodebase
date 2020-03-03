// P4762.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int T, n, ptot, last_ptr, dp[MAX_N];
char str[MAX_N];

struct node
{
    int ch[26], dep, link, trans;
} nodes[MAX_N];

void init()
{
    for (int i = 0; i <= ptot; i++)
        memset(nodes[i].ch, 0, sizeof(nodes[i].ch)), nodes[i].dep = nodes[i].link = nodes[i].trans = 0;
    nodes[0].link = 1, nodes[1].dep = -1, nodes[1].link = 0, nodes[0].dep = 0;
    ptot = 1, last_ptr = 0;
}

int jumpLink(int p, int pos)
{
    while (str[pos] != str[pos - nodes[p].dep - 1])
        p = nodes[p].link;
    return p;
}

void insert(int pos)
{
    int pre = jumpLink(last_ptr, pos);
    if (nodes[pre].ch[str[pos] - 'A'] == 0)
    {
        int p = ++ptot;
        nodes[p].dep = nodes[pre].dep + 2;
        nodes[p].link = nodes[jumpLink(nodes[pre].link, pos)].ch[str[pos] - 'A'];
        nodes[pre].ch[str[pos] - 'A'] = p;
        if (nodes[p].dep <= 2)
            nodes[p].trans = nodes[p].link;
        else
        {
            int q = nodes[pre].trans;
            while (str[pos - 1 - nodes[q].dep] != str[pos] || ((nodes[q].dep + 2) << 1) > nodes[p].dep)
                q = nodes[q].link;
            nodes[p].trans = nodes[q].ch[str[pos] - 'A'];
        }
    }
    last_ptr = nodes[pre].ch[str[pos] - 'A'];
}

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%s", str + 1), n = strlen(str + 1), init();
        for (int i = 1; i <= n; i++)
            insert(i);
        for (int i = 2; i <= ptot; i++)
            dp[i] = nodes[i].dep;
        queue<int> q;
        q.push(0), dp[0] = 1;
        int ans = n;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (int i = 0; i < 26; i++)
                if (nodes[u].ch[i])
                {
                    int v = nodes[u].ch[i], g = nodes[v].trans;
                    dp[v] = dp[u] + 1;
                    dp[v] = min(dp[v], dp[g] + 1 + (nodes[v].dep >> 1) - nodes[g].dep);
                    ans = min(ans, dp[v] + n - nodes[v].dep);
                    q.push(v);
                }
        }
        printf("%d\n", ans);
    }
    return 0;
}