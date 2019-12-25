// P4248.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 501000;

int n;
long long sum;
char str[MAX_N];

namespace SAM
{

struct node
{
    int ch[26], link, dep;
} nodes[MAX_N << 1];

int last_ptr = 1, ptot = 1, siz[MAX_N << 1], bucket[MAX_N], rnk[MAX_N << 1];

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

void radixSort()
{
    for (int i = 1; i <= ptot; i++)
        bucket[nodes[i].dep]++;
    for (int i = 1; i <= ptot; i++)
        bucket[i] += bucket[i - 1];
    for (int i = 1; i <= ptot; i++)
        rnk[bucket[nodes[i].dep]--] = i;
    for (int i = ptot; i >= 1; i--)
        if (nodes[rnk[i]].link != 0)
            siz[nodes[rnk[i]].link] += siz[rnk[i]];
    for (int i = ptot; i >= 1; i--)
        sum += 1LL * (nodes[rnk[i]].dep - nodes[nodes[rnk[i]].link].dep) * (siz[rnk[i]]) * (n - siz[rnk[i]]);
}

} // namespace SAM

int main()
{
    scanf("%s", str + 1), n = strlen(str + 1);
    for (int i = 1; i <= n; i++)
        SAM::insert(str[i] - 'a'), SAM::siz[SAM::last_ptr]++;
    SAM::radixSort();
    printf("%lld\n", sum);
    return 0;
}