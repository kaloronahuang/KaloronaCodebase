// CF316G3.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

int n, lens[11], li[11], ri[11];
char str[11][MAX_N];

// SAM;

struct node
{
    int ch[26], dep, link;
} nodes[MAX_N];

int ptot = 1, last_ptr = 1, siz[11][MAX_N], rnk[MAX_N], bucket[MAX_N];
vector<int> G[MAX_N];

void insert(int c)
{
    int pre = last_ptr;
    if (nodes[pre].ch[c] != 0)
    {
        int q = nodes[pre].ch[c];
        if (nodes[q].dep == nodes[pre].dep + 1)
            last_ptr = q;
        else
        {
            int clone = ++ptot;
            nodes[clone] = nodes[q], nodes[clone].dep = nodes[pre].dep + 1;
            last_ptr = clone, nodes[q].link = clone;
            while (pre && nodes[pre].ch[c] == q)
                nodes[pre].ch[c] = clone, pre = nodes[pre].link;
        }
    }
    else
    {
        int p = last_ptr = ++ptot;
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
}

int main()
{
    scanf("%s%d", str[0] + 1, &n), lens[0] = strlen(str[0] + 1);
    for (int i = 1; str[0][i]; i++)
        insert(str[0][i] - 'a'), siz[0][last_ptr]++;
    for (int i = 1; i <= n; i++)
    {
        scanf("%s%d%d", str[i] + 1, &li[i], &ri[i]), lens[i] = strlen(str[i] + 1);
        last_ptr = 1;
        for (int j = 1; str[i][j]; j++)
            insert(str[i][j] - 'a'), siz[i][last_ptr]++;
    }
    for (int i = 1; i <= ptot; i++)
        bucket[nodes[i].dep]++;
    for (int i = 1; i <= ptot; i++)
        bucket[i] += bucket[i - 1];
    for (int i = 1; i <= ptot; i++)
        rnk[bucket[nodes[i].dep]--] = i;
    for (int i = ptot; i >= 2; i--)
        for (int j = 0; j <= n; j++)
            siz[j][nodes[rnk[i]].link] += siz[j][rnk[i]];
    long long ans = 0;
    for (int i = 2; i <= ptot; i++)
        if (siz[0][i])
        {
            bool flag = true;
            for (int j = 1; j <= n; j++)
                flag &= li[j] <= siz[j][i] && siz[j][i] <= ri[j];
            if (flag)
                ans += nodes[i].dep - nodes[nodes[i].link].dep;
        }
    printf("%lld\n", ans);
    return 0;
}