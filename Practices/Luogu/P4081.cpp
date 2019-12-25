// P4081.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e5 + 200;

int T, len[MAX_N], gtot, ans[MAX_N];
char str[MAX_N], gen[MAX_N];

namespace SAM
{

struct node
{
    int ch[26], link, dep, vis;
} nodes[MAX_N];

int last_ptr = 1, ptot = 1;

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
            nodes[clone] = nodes[q];
            nodes[clone].dep = nodes[pre].dep + 1;
            nodes[p].link = nodes[q].link = clone;
            while (pre && nodes[pre].ch[c] == q)
                nodes[pre].ch[c] = clone, pre = nodes[pre].link;
        }
    }
}

void update(int u, int org)
{
    while (u && nodes[u].vis != org && nodes[u].vis != -1)
    {
        if (nodes[u].vis != 0)
            nodes[u].vis = -1;
        else
            nodes[u].vis = org;
        u = nodes[u].link;
    }
}

} // namespace SAM

int main()
{
    scanf("%d", &T);
    for (int id = 1; id <= T; id++)
    {
        scanf("%s", str + 1), SAM::last_ptr = 1;
        for (int i = 1; str[i] != '\0'; i++)
        {
            gen[++gtot] = str[i], len[id]++;
            SAM::insert(str[i] - 'a');
        }
    }
    int ptr = 0;
    for (int idx = 1; idx <= T; idx++)
        for (int i = 1, p = 1; i <= len[idx]; i++)
            SAM::update(p = SAM::nodes[p].ch[gen[++ptr] - 'a'], idx);
    for (int i = 1; i <= SAM::ptot; i++)
        if (SAM::nodes[i].vis != -1)
            ans[SAM::nodes[i].vis] += SAM::nodes[i].dep - SAM::nodes[SAM::nodes[i].link].dep;
    for (int i = 1; i <= T; i++)
        printf("%d\n", ans[i]);
    return 0;
}