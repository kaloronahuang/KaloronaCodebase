// LOJ3108.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e6 + 200;

int T, n, limit, diff[MAX_N];
char str[MAX_N];

namespace SAM
{

struct node
{
    int ch[26], dep, link, siz;
    void clear(int dep) { memset(ch, 0, sizeof(ch)), this->dep = dep, link = siz = 0; }
} nodes[MAX_N << 1];

int ptot, last_ptr, idx[MAX_N], bucket[MAX_N];

void initialize() { ptot = last_ptr = 1, nodes[1].clear(0); }

void insert(int c)
{
    int pre = last_ptr, p = last_ptr = ++ptot;
    nodes[p].clear(nodes[pre].dep + 1);
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
            nodes[p].link = nodes[q].link = clone, nodes[clone].siz = 0;
            while (pre && nodes[pre].ch[c] == q)
                nodes[pre].ch[c] = clone, pre = nodes[pre].link;
        }
    }
}

void radixSort()
{
    memset(idx, 0, sizeof(idx)), memset(bucket, 0, sizeof(bucket));
    for (int i = 1; i <= ptot; i++)
        bucket[nodes[i].dep]++;
    for (int i = 1; i <= ptot; i++)
        bucket[i] += bucket[i - 1];
    for (int i = 1; i <= ptot; i++)
        idx[bucket[nodes[i].dep]--] = i;
    for (int i = ptot; i >= 1; i--)
        if (nodes[idx[i]].link != 0)
            nodes[nodes[idx[i]].link].siz += nodes[idx[i]].siz;
    for (int i = 1; i <= ptot; i++)
        if (nodes[i].siz == limit)
            diff[nodes[i].dep + 1]--, diff[nodes[nodes[i].link].dep + 1]++;
    for (int i = 1; i <= ptot; i++)
        diff[i] += diff[i - 1];
}

}; // namespace SAM

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        memset(diff, 0, sizeof(diff));
        scanf("%s%d", str + 1, &limit), n = strlen(str + 1);
        SAM::initialize();
        for (int i = 1; i <= n; i++)
            SAM::insert(str[i] - 'a'), SAM::nodes[SAM::last_ptr].siz++;
        SAM::radixSort();

        int ans = 0;
        for (int i = 1; i <= n; i++)
            if (diff[i] >= diff[ans])
                ans = i;
        if (diff[ans] == 0)
            puts("-1");
        else
            printf("%d\n", ans);
    }
    return 0;
}