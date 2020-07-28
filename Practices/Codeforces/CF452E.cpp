// CF452E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 6e5 + 200, mod = 1e9 + 7;

int n[3], last_ptr = 1, ptot = 1, siz[3][MAX_N], srange, bucket[MAX_N], rnk[MAX_N], ansBox[MAX_N];
char str[3][MAX_N];

struct node
{
    int ch[26], dep, link;
} nodes[MAX_N];

void mark(int l, int r, int val) { ansBox[l] = (0LL + ansBox[l] + val) % mod, ansBox[r + 1] = (0LL + ansBox[r + 1] + mod - val) % mod; }

void insert(int c)
{
    int pre = last_ptr;
    if (nodes[pre].ch[c])
    {
        int q = nodes[pre].ch[c];
        if (nodes[q].dep == nodes[pre].dep + 1)
            last_ptr = q;
        else
        {
            int clone = ++ptot;
            nodes[clone] = nodes[q], nodes[clone].dep = nodes[pre].dep + 1;
            nodes[q].link = last_ptr = clone;
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

void radixSort()
{
    for (int i = 1; i <= ptot; i++)
        bucket[nodes[i].dep]++;
    for (int i = 1; i <= ptot; i++)
        bucket[i] += bucket[i - 1];
    for (int i = 1; i <= ptot; i++)
        rnk[bucket[nodes[i].dep]--] = i;
    for (int i = ptot; i >= 2; i--)
    {
        int u = rnk[i];
        for (int j = 0; j < 3; j++)
            siz[j][nodes[u].link] += siz[j][u];
    }
}

int main()
{
    for (int i = 0; i < 3; i++)
        scanf("%s", str[i] + 1), n[i] = strlen(str[i] + 1);
    srange = *min_element(n, n + 3);
    for (int i = 0; i < 3; i++, last_ptr = 1)
        for (int j = 1; str[i][j]; j++)
            insert(str[i][j] - 'a'), siz[i][last_ptr]++;
    radixSort();
    for (int i = 2; i <= ptot; i++)
    {
        int fa = nodes[i].link, tot = 1LL * siz[0][i] * siz[1][i] % mod * siz[2][i] % mod;
        if (tot && nodes[i].dep <= srange)
            mark(nodes[fa].dep + 1, nodes[i].dep, tot);
    }
    for (int i = 1; i <= srange; i++)
        ansBox[i] = (0LL + ansBox[i] + ansBox[i - 1]) % mod, printf("%d ", ansBox[i]);
    puts("");
    return 0;
}