// P4188.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 100100;

struct node
{
    int l, r, t;
    bool operator<(const node &nd) const { return l < nd.l; }
} nodes[MAX_N];

int n;
ll ans = 0;

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &nodes[i].l, &nodes[i].r), nodes[i].t = nodes[i].r - nodes[i].l;
    sort(nodes + 1, nodes + 1 + n);
    int len = 0, p = 0;
    bool flag = false;
    for (int i = 1; i <= n; i++)
        if (nodes[i].r <= p)
            flag = true;
        else
        {
            len += min(nodes[i].r - nodes[i].l, nodes[i].r - p);
            nodes[i].t = min(nodes[i].r - nodes[i].l, nodes[i].r - p);
            if (i > 1 && nodes[i].l < p)
                nodes[i - 1].t -= (p - nodes[i].l);
            p = nodes[i].r;
        }
    int tmp = 0;
    if (flag)
        printf("%d", len), exit(0);
    for (int i = 1; i <= n; i++)
        tmp = max(tmp, len - nodes[i].t);
    printf("%d", tmp);
    return 0;
}