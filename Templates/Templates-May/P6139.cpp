// P6139.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e6 + 200;

int n, pos[MAX_N];
char str[MAX_N];

namespace Trie
{

    int ch[MAX_N][26], ptot = 1, up[MAX_N], depot[MAX_N];

    void insert()
    {
        int p = 1;
        for (int i = 1; str[i]; i++)
        {
            if (ch[p][str[i] - 'a'] == 0)
                ch[p][str[i] - 'a'] = ++ptot, up[ptot] = p, depot[ptot] = str[i] - 'a';
            p = ch[p][str[i] - 'a'];
        }
    }

} // namespace Trie

namespace SAM
{

    struct node
    {
        int ch[26], link, dep;
    } nodes[MAX_N];

    int ptot = 1, last_ptr = 1;

    void insert(int c)
    {
        int pre = last_ptr, p = last_ptr = ++ptot;
        nodes[p].dep = nodes[pre].dep + 1;
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
                nodes[clone] = nodes[q], nodes[clone].dep = nodes[pre].dep + 1;
                nodes[p].link = nodes[q].link = clone;
                while (pre && nodes[pre].ch[c] == q)
                    nodes[pre].ch[c] = clone, pre = nodes[pre].link;
            }
        }
    }

} // namespace SAM

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%s", str + 1), Trie::insert();
    queue<int> q;
    for (int i = 0; i < 26; i++)
        if (Trie::ch[1][i])
            q.push(Trie::ch[1][i]);
    pos[1] = 1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        SAM::last_ptr = pos[Trie::up[u]];
        SAM::insert(Trie::depot[u]);
        pos[u] = SAM::last_ptr;
        for (int i = 0; i < 26; i++)
            if (Trie::ch[u][i])
                q.push(Trie::ch[u][i]);
    }
    long long ans = 0;
    for (int i = 2; i <= SAM::ptot; i++)
        ans += SAM::nodes[i].dep - SAM::nodes[SAM::nodes[i].link].dep;
    printf("%lld\n", ans);
    return 0;
}