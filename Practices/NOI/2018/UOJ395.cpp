// UOJ395.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1.5e6 + 200;

int n, q, max_len[MAX_N << 1];
char str[MAX_N];

struct SAM
{

    struct node
    {
        int ch[26], link, dep;
    } nodes[MAX_N << 1];

    int ptot = 1, last_ptr = 1, pos[MAX_N << 1];

    void clear()
    {
        for (int i = 1; i <= ptot; i++)
            memset(nodes[i].ch, 0, sizeof(nodes[i].ch)), nodes[i].link = nodes[i].dep = pos[i] = 0;
        last_ptr = ptot = 1;
    }

    void insert(int c, int src)
    {
        int pre = last_ptr, p = last_ptr = ++ptot;
        nodes[p].dep = nodes[pre].dep + 1, pos[p] = src;
        while (pre && nodes[pre].ch[c] == 0)
            nodes[pre].ch[c] = p, pre = nodes[pre].link;
        if (pre == 0)
            nodes[p].link = 1;
        else
        {
            int q = nodes[pre].ch[c];
            if (nodes[q].dep == nodes[pre].dep + 1)
                nodes[p].link = q;
            else
            {
                int clone = ++ptot;
                nodes[clone] = nodes[q], nodes[clone].dep = nodes[pre].dep + 1, pos[clone] = pos[q];
                nodes[p].link = nodes[q].link = clone;
                while (pre && nodes[pre].ch[c] == q)
                    nodes[pre].ch[c] = clone, pre = nodes[pre].link;
            }
        }
    }

    void match()
    {
        int p = 1, len = 0;
        for (int i = 1; str[i]; i++)
        {
            while (p && nodes[p].ch[str[i] - 'a'] == 0)
                p = nodes[p].link, len = nodes[p].dep;
            if (p == 0)
                p = 1, len = 0;
            else
                len++, p = nodes[p].ch[str[i] - 'a'];
            max_len[i] = len;
        }
    }

} tr[2];

int main()
{
    scanf("%s", str + 1), n = strlen(str + 1);
    for (int i = 1; i <= n; i++)
        tr[0].insert(str[i] - 'a', i);
    scanf("%d", &q);
    while (q--)
    {
        int l, r;
        scanf("%s%d%d", str + 1, &l, &r);
        tr[0].match(), tr[1].clear();
        for (int i = 1; str[i]; i++)
            tr[1].insert(str[i] - 'a', i);
        long long ans = 0;
        for (int i = 1; i <= tr[1].ptot; i++)
            ans += max(0, tr[1].nodes[i].dep - max(tr[1].nodes[tr[1].nodes[i].link].dep, max_len[tr[1].pos[i]]));
        printf("%lld\n", ans);
    }
    return 0;
}