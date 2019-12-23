// LOJ2064.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 5e5 + 200;

struct node
{
    int ch[26], siz[2], link, dep;
} nodes[MAX_N << 1];

int last_ptr = 1, ptot = 1, bucket[MAX_N << 1], n1, n2, rnk[MAX_N << 1];
ll ans;
char str1[MAX_N], str2[MAX_N];

void insert(int c, int typ)
{
    int pre = last_ptr, p = last_ptr = ++ptot;
    nodes[p].dep = nodes[pre].dep + 1;
    if (typ == 0)
        nodes[p].siz[0] = 1;
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
            nodes[clone] = nodes[q], nodes[clone].siz[0] = nodes[clone].siz[1] = 0;
            nodes[clone].dep = nodes[pre].dep + 1;
            nodes[p].link = nodes[q].link = clone;
            while (pre && nodes[pre].ch[c] == q)
                nodes[pre].ch[c] = clone, pre = nodes[pre].link;
        }
    }
}

void radixSort()
{
    for (int i = 1; i <= ptot; i++)
        bucket[nodes[i].dep]++;
    for (int i = 1; i <= ptot; i++)
        bucket[i] += bucket[i - 1];
    for (int i = ptot; i >= 1; i--)
        rnk[bucket[nodes[i].dep]--] = i;
    for (int i = ptot; i >= 1; i--)
        if (nodes[rnk[i]].link != 0)
        {
            nodes[nodes[rnk[i]].link].siz[0] += nodes[rnk[i]].siz[0];
            nodes[nodes[rnk[i]].link].siz[1] += nodes[rnk[i]].siz[1];
        }
    for (int i = 1; i <= ptot; i++)
        ans += 1LL * nodes[i].siz[0] * nodes[i].siz[1] * (nodes[i].dep - nodes[nodes[i].link].dep);
}

int main()
{
    scanf("%s%s", str1 + 1, str2 + 1);
    n1 = strlen(str1 + 1), n2 = strlen(str2 + 1);
    for (int i = 1; i <= n1; i++)
        insert(str1[i] - 'a', 0);
    last_ptr = 1;
    for (int i = 1, p = 1; i <= n2; i++)
    {
        insert(str2[i] - 'a', 1);
        p = nodes[p].ch[str2[i] - 'a'];
        nodes[p].siz[1] = 1;
    }
    radixSort();
    printf("%lld\n", ans);
    return 0;
}