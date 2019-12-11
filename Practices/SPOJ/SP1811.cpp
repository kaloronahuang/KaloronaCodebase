// SP1811.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

int n1, n2, ptot = 1, last_ptr = 1;
char str1[MAX_N], str2[MAX_N];

struct node
{
    int ch[26], link, len;
} nodes[MAX_N];

void insert(int c)
{
    int pre = last_ptr, p = last_ptr = ++ptot;
    nodes[p].len = nodes[pre].len + 1;
    for (; pre && nodes[pre].ch[c] == 0; pre = nodes[pre].link)
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
            nodes[clone] = nodes[q];
            nodes[clone].len = nodes[pre].len + 1;
            nodes[q].link = nodes[p].link = clone;
            for (; nodes[pre].ch[c] == q; pre = nodes[pre].link)
                nodes[pre].ch[c] = clone;
        }
    }
}

int main()
{
    scanf("%s%s", str1 + 1, str2 + 1);
    n1 = strlen(str1 + 1), n2 = strlen(str2 + 1);
    for (int i = 1; i <= n1; i++)
        insert(str1[i] - 'a');
    int ans = 0, p = 1, len = 0;
    for (int i = 1; i <= n2; i++)
    {
        int c = str2[i] - 'a';
        if (nodes[p].ch[c])
            len++, p = nodes[p].ch[c];
        else
        {
            for (; p && nodes[p].ch[c] == 0; p = nodes[p].link)
                ;
            if (p == 0)
                len = 0, p = 1; // no such substr;
            else
                len = nodes[p].len + 1, p = nodes[p].ch[c];
        }
        ans = max(ans, len);
    }
    printf("%d\n", ans);
    return 0;
}