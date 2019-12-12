// SP7258.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1010000;

int ptot = 1, last_ptr = 1, T, bucket[MAX_N], idx[MAX_N];
char opt[MAX_N];

struct node
{
    int ch[26], link, len, siz;
} nodes[MAX_N];

void insert(int c)
{
    int pre = last_ptr, p = last_ptr = ++ptot;
    nodes[p].len = nodes[pre].len + 1, nodes[p].siz = 1;
    for (; pre != 0 && nodes[pre].ch[c] == 0; pre = nodes[pre].link)
        nodes[pre].ch[c] = p;
    if (pre == 0)
        nodes[p].link = 1;
    else
    {
        int q = nodes[pre].ch[c];
        if (nodes[q].len == nodes[pre].len + 1)
            nodes[p].link = q;
        else
        {
            int clone = ++ptot;
            nodes[clone] = nodes[q], nodes[clone].siz = 1;
            nodes[clone].len = nodes[pre].len + 1;
            nodes[q].link = nodes[p].link = clone;
            for (; p != 0 && nodes[pre].ch[c] == q; pre = nodes[pre].link)
                nodes[pre].ch[c] = clone;
        }
    }
}

int main()
{
    scanf("%s", opt + 1);
    for (int i = 1; opt[i] != '\0'; i++)
        insert(opt[i] - 'a');
    for (int i = 2; i <= ptot; i++)
        bucket[nodes[i].len]++;
    for (int i = 1; i <= ptot; i++)
        bucket[i] += bucket[i - 1];
    for (int i = 2; i <= ptot; i++)
        idx[bucket[nodes[i].len]--] = i;
    for (int i = ptot - 1; i >= 1; i--)
        for (int ch = 0; ch < 26; ch++)
            nodes[idx[i]].siz += nodes[nodes[idx[i]].ch[ch]].siz;
    scanf("%d", &T);
    while (T--)
    {
        int k, p = 1;
        scanf("%d", &k);
        while (k)
            for (int i = 0; i < 26; i++)
                if (k > nodes[nodes[p].ch[i]].siz)
                    k -= nodes[nodes[p].ch[i]].siz;
                else
                {
                    p = nodes[p].ch[i], putchar(i + 'a'), k--;
                    break;
                }
        puts("");
    }
    return 0;
}