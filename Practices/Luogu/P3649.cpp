// P3649.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 600100;

typedef long long ll;

int n, pos[MAX_N], match[MAX_N], tag[MAX_N];
char str[MAX_N], tmp[MAX_N];
ll gans;

namespace SAM
{

struct node
{
    int ch[26], dep, link;
} nodes[MAX_N << 1];

int ptot = 1, last_ptr = 1, siz[MAX_N], bucket[MAX_N], idx[MAX_N], dep[MAX_N], fa[20][MAX_N];

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

void initialize()
{
    for (int i = 1; i <= n; i++)
        insert(str[i] - 'a'), siz[last_ptr]++, tag[i] = last_ptr;
    for (int i = 1; i <= ptot; i++)
        bucket[nodes[i].dep]++;
    for (int i = 1; i <= ptot; i++)
        bucket[i] += bucket[i - 1];
    for (int i = 1; i <= ptot; i++)
        idx[bucket[nodes[i].dep]--] = i;
    for (int i = 1; i <= ptot; i++)
        dep[idx[i]] = dep[nodes[idx[i]].link] + 1;
    for (int i = ptot; i >= 1; i--)
        if (nodes[idx[i]].link)
            siz[nodes[idx[i]].link] += siz[idx[i]], fa[0][idx[i]] = nodes[idx[i]].link;
    for (int i = 1; i <= 19; i++)
        for (int j = 1; j <= ptot; j++)
            fa[i][j] = fa[i - 1][fa[i - 1][j]];
}

void update(int l, int r)
{
    if (l < 1 || r > n)
        return;
    // go up;
    int p = tag[r];
    for (int i = 19; i >= 0; i--)
        if (fa[i][p] != 0 && nodes[fa[i][p]].dep >= (r - l + 1))
            p = fa[i][p];
    gans = max(gans, 1LL * (r - l + 1) * siz[p]);
}

} // namespace SAM

void manacher()
{
    int len = 0;
    tmp[++len] = '!';
    for (int i = 1; i <= n; i++)
        tmp[++len] = '#', tmp[++len] = str[i], pos[len] = i;
    tmp[++len] = '#', tmp[++len] = '?';
    int ptr = 0, max_val = 0;
    for (int i = 1; i <= len; i++)
    {
        if (i < max_val)
            match[i] = min(max_val - i, match[(ptr << 1) - i]);
        else
            match[i] = 1;
        SAM::update(pos[i - match[i] + 2], pos[i + match[i] - 2]);
        while (tmp[i - match[i]] == tmp[i + match[i]])
            match[i]++, SAM::update(pos[i - match[i] + 2], pos[i + match[i] - 2]);
        if (i + match[i] > max_val)
            max_val = i + match[i], ptr = i;
    }
}

int main()
{
    scanf("%s", str + 1), n = strlen(str + 1);
    SAM::initialize(), manacher(), printf("%lld\n", gans);
    return 0;
}