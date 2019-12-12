// P4070.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 1e6 + 200;

struct node
{
    map<int, int> ch;
    int link, len;
} nodes[MAX_N];

int n, ptot = 1, last_ptr = 1, opt;
ll ans;

void insert(int c)
{
    int pre = last_ptr, p = last_ptr = ++ptot;
    nodes[p].len = nodes[pre].len + 1;
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
            nodes[clone] = nodes[q];
            nodes[clone].len = nodes[pre].len + 1;
            nodes[q].link = nodes[p].link = clone;
            for (; nodes[pre].ch[c] == q; pre = nodes[pre].link)
                nodes[pre].ch[c] = clone;
        }
    }
    ans += nodes[p].len - nodes[nodes[p].link].len;
}

int main()
{
    scanf("%d", &n);
    while (n--)
    {
        scanf("%d", &opt);
        insert(opt);
        printf("%lld\n", ans);
    }
    return 0;
}