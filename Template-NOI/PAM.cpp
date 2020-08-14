// PAM.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int T, n, ptot, last_ptr, pstot, dp[MAX_N];
char pS[MAX_N], str[MAX_N];

struct node
{
    int ch[26], link, dep, trans;
} nodes[MAX_N];

int create(int len)
{
    ptot++, memset(nodes[ptot].ch, 0, sizeof(nodes[ptot].ch));
    nodes[ptot].dep = len;
    nodes[ptot].link = nodes[ptot].trans = 0;
    return ptot;
}

void clear()
{
    ptot = -1, last_ptr = 0;
    pS[pstot = 0] = '$';
    create(0), create(-1);
    nodes[0].link = 1;
}

int jump(int p)
{
    while (pS[pstot - nodes[p].dep - 1] != pS[pstot])
        p = nodes[p].link;
    return p;
}

void insert(int c)
{
    pS[++pstot] = c + 'A';
    int pre = jump(last_ptr);
    if (nodes[pre].ch[c] == 0)
    {
        int p = create(nodes[pre].dep + 2);
        nodes[p].link = nodes[jump(nodes[pre].link)].ch[c];
        nodes[pre].ch[c] = p;
        if (nodes[p].dep <= 2)
            nodes[p].trans = nodes[p].link;
        else
        {
            int q = nodes[pre].trans;
            while (str[pstot - 1 - nodes[q].dep] != str[pstot] || ((nodes[q].dep + 2) << 1) > nodes[p].dep)
                q = nodes[q].link;
            nodes[p].trans = nodes[q].ch[c];
        }
    }
    last_ptr = nodes[pre].ch[c];
}

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%s", str + 1), clear();
        n = strlen(str + 1);
        for (int i = 1; i <= n; i++)
            insert(str[i] - 'A');
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