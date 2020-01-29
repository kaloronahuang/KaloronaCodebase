// CF235C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

int n, q;
char str[MAX_N << 1];

struct node
{
    int ch[26], link, dep;
} nodes[MAX_N << 1];

int siz[MAX_N << 1], idx[MAX_N << 1], bucket[MAX_N << 1], last_ptr = 1, ptot = 1, up[25][MAX_N << 1];

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
        up[0][i] = nodes[i].link;
    for (int i = 1; i < 25; i++)
        for (int j = 1; j <= ptot; j++)
            up[i][j] = up[i - 1][up[i - 1][j]];
    for (int i = 1; i <= ptot; i++)
        bucket[nodes[i].dep]++;
    for (int i = 1; i <= ptot; i++)
        bucket[i] += bucket[i - 1];
    for (int i = 1; i <= ptot; i++)
        idx[bucket[nodes[i].dep]--] = i;
    for (int i = ptot; i >= 1; i--)
        if (nodes[idx[i]].link != 0)
            siz[nodes[idx[i]].link] += siz[idx[i]];
}

int main()
{
    scanf("%s", str + 1), n = strlen(str + 1);
    for (int i = 1; i <= n; i++)
        insert(str[i] - 'a'), siz[last_ptr]++;
    radixSort();
    scanf("%d", &q);
    while (q--)
    {
        scanf("%s", str + 1);
        int len = strlen(str + 1);
        for (int i = 1; i <= len - 1; i++)
            str[i + len] = str[i];
        str[(len << 1)] = '\0';
        set<int> st;
        for (int i = 1, p = 1, clen = 0; i < (len << 1); i++)
        {
            int c = str[i] - 'a';
            while (p && nodes[p].ch[c] == 0)
                p = nodes[p].link, clen = nodes[p].dep;
            if (p == 0)
                p = 1, clen = 0;
            else
                p = nodes[p].ch[c], clen++;
            if (clen > len)
            {
                clen--;
                if (clen == nodes[nodes[p].link].dep)
                    p = nodes[p].link;
            }
            if (clen == len)
                st.insert(p);
        }
        int ans = 0;
        while (!st.empty())
            ans += siz[*st.begin()], st.erase(st.begin());
        printf("%d\n", ans);
    }
    return 0;
}