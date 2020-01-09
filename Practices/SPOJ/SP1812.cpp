// SP1812.cpp
#include <bits/stdc++.h>
#pragma GCC optimize(2)

using namespace std;

const int MAX_N = 1e5 + 200;

struct node
{
    int ch[26], link, dep, curt, min_val;
} nodes[MAX_N << 1];

int ptot = 1, last_ptr = 1, idx[MAX_N << 1], bucket[MAX_N << 1];
char tmp[MAX_N << 1];

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
        idx[bucket[nodes[i].dep]--] = i;
}

void processString(char *str)
{
    int p = 1, len = 0;
    for (int i = 1; i <= ptot; i++)
        nodes[i].curt = 0;
    for (int ptr = 1; str[ptr] != '\0'; ptr++)
    {
        if (nodes[p].ch[str[ptr] - 'a'] != 0)
            p = nodes[p].ch[str[ptr] - 'a'], len++;
        else
        {
            while (p && nodes[p].ch[str[ptr] - 'a'] == 0)
                p = nodes[p].link;
            if (p == 0)
                p = 1, len = 0;
            else
                len = nodes[p].dep + 1, p = nodes[p].ch[str[ptr] - 'a'];
        }
        nodes[p].curt = max(nodes[p].curt, len);
    }
    for (int i = ptot; i >= 1; i--)
    {
        int p = idx[i];
        nodes[p].min_val = min(nodes[p].min_val, nodes[p].curt);
        if (nodes[p].curt >= nodes[p].dep && nodes[p].link != 0)
            nodes[nodes[p].link].curt = nodes[nodes[p].link].dep;
    }
}

int main()
{
    scanf("%s", tmp + 1);
    for (int i = 1; tmp[i] != '\0'; i++)
        insert(tmp[i] - 'a');
    radixSort();
    for (int i = 1; i <= ptot; i++)
        nodes[i].min_val = nodes[i].dep;
    while (scanf("%s", tmp + 1) != EOF)
        processString(tmp);
    int ans = 0;
    for (int i = 1; i <= ptot; i++)
        ans = max(ans, nodes[i].min_val);
    printf("%d\n", ans);
    return 0;
}