// CF802I.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int T, n, rnk[MAX_N], bucket[MAX_N];
char str[MAX_N];

namespace SAM
{

    struct node
    {
        int ch[26], dep, link;
        void clear() { memset(ch, 0, sizeof(ch)), dep = link = 0; }
    } nodes[MAX_N];

    int last_ptr = 1, ptot = 1, siz[MAX_N];

    void initialize() { last_ptr = ptot = 1, memset(siz, 0, sizeof(siz)), nodes[1].clear(); }

    void insert(int c)
    {
        int pre = last_ptr, p = last_ptr = ++ptot;
        nodes[p].clear(), nodes[p].dep = nodes[pre].dep + 1;
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
                nodes[clone].clear();
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
    scanf("%d", &T);
    while (T--)
    {
        scanf("%s", str + 1), n = strlen(str + 1);
        SAM::initialize();
        for (int i = 1; i <= n; i++)
            SAM::insert(str[i] - 'a'), SAM::siz[SAM::last_ptr]++;
        memset(bucket, 0, sizeof(bucket)), memset(rnk, 0, sizeof(rnk));
        for (int i = 1; i <= SAM::ptot; i++)
            bucket[SAM::nodes[i].dep]++;
        for (int i = 1; i <= SAM::ptot; i++)
            bucket[i] += bucket[i - 1];
        for (int i = 1; i <= SAM::ptot; i++)
            rnk[bucket[SAM::nodes[i].dep]--] = i;
        for (int i = SAM::ptot; i >= 2; i--)
            SAM::siz[SAM::nodes[rnk[i]].link] += SAM::siz[rnk[i]];
        long long ans = 0;
        for (int i = 1; i <= SAM::ptot; i++)
            ans += 1LL * (SAM::nodes[i].dep - SAM::nodes[SAM::nodes[i].link].dep) * SAM::siz[i] * SAM::siz[i];
        printf("%lld\n", ans);
    }
    return 0;
}