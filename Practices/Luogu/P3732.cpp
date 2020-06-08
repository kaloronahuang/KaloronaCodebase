// P3732.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

typedef pair<int, int> pii;
typedef long long ll;

int n, q, ptot = 1, last_ptr = 1, nearest[MAX_N << 2], pos[MAX_N], lcp[MAX_N << 2];
int qu[MAX_N], wi[MAX_N], T, latest[MAX_N << 2];
char str[MAX_N];
vector<pii> queries[MAX_N];
ll ansBox[MAX_N];

struct node
{
    int ch[2], link, dep;
} nodes[MAX_N << 2];

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

int main()
{
    scanf("%d%d%s", &n, &q, str + 1);
    for (int i = n; i >= 1; i--)
        insert(str[i] - '0'), pos[i] = last_ptr;
    for (int i = 1, l, r; i <= q; i++)
    {
        scanf("%d%d", &l, &r);
        queries[r].push_back(make_pair(l, i));
    }
    for (int i = 1; i <= n; i++)
    {
        int p = pos[i];
        while (p)
        {
            lcp[nodes[p].dep] = max(lcp[nodes[p].dep], latest[p]);
            if (lcp[nodes[p].dep])
                T = max(T, nodes[p].dep);
            latest[p] = max(latest[p], i), p = nodes[p].link;
        }
        for (pii u : queries[i])
        {
            int top = 0;
            for (int i = 1; i <= T; i++)
                if (lcp[i])
                {
                    while (top && lcp[i] >= qu[top])
                        top--;
                    qu[++top] = lcp[i], wi[top] = i;
                }
            qu[top + 1] = 0;
            for (int i = 2; i <= top + 1; i++)
            {
                if (qu[i] < u.first)
                {
                    ansBox[u.second] += (qu[i - 1] - u.first + 1) * wi[i - 1];
                    break;
                }
                ansBox[u.second] += (qu[i - 1] - qu[i]) * wi[i - 1];
            }
        }
    }
    for (int i = 1; i <= q; i++)
        printf("%lld\n", ansBox[i]);
    return 0;
}