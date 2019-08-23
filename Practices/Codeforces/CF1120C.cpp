// CF1120C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

struct node
{
    int ch[26], link, dep, occur = 0x3f3f3f3f;
} nodes[MAX_N];

int n, ca, cb, ptot, last_cur, bucketA[MAX_N], bucketB[MAX_N];
int pos[5001][5001], dp[MAX_N];
char str[MAX_N];

void sam_initialize() { last_cur = ++ptot; }

void insert(int c, int pos)
{
    int cur = ++ptot;
    nodes[cur].dep = nodes[last_cur].dep + 1;
    nodes[cur].occur = pos;
    int p = last_cur;
    while (p && nodes[p].ch[c] == 0)
        nodes[p].ch[c] = cur, p = nodes[p].link;

    if (p == 0)
        nodes[cur].link = 1;
    else
    {
        int q = nodes[p].ch[c];

        if (nodes[p].dep + 1 == nodes[q].dep)
            nodes[cur].link = q;
        else
        {
            int clone = ++ptot;
            nodes[clone].dep = nodes[p].dep + 1;
            memcpy(nodes[clone].ch, nodes[q].ch, sizeof(nodes[q].ch));
            nodes[clone].link = nodes[q].link;
            while (p && nodes[p].ch[c] == q)
                nodes[p].ch[c] = clone, p = nodes[p].link;
            nodes[q].link = nodes[cur].link = clone;
        }
    }

    last_cur = cur;
}

void stringSort()
{
    for (int i = 1; i <= ptot; i++)
        bucketA[i] = 0;
    for (int i = 1; i <= ptot; i++)
        bucketA[nodes[i].dep]++;
    for (int i = 1; i <= ptot; i++)
        bucketA[i] += bucketA[i - 1];
    for (int i = 1; i <= ptot; i++)
        bucketB[bucketA[nodes[i].dep]--] = i;

    for (int i = ptot; i >= 1; i--)
        nodes[nodes[bucketB[i]].link].occur = min(nodes[nodes[bucketB[i]].link].occur, nodes[bucketB[i]].occur);
}

int main()
{
    sam_initialize();
    scanf("%d%d%d%s", &n, &ca, &cb, str + 1);
    for (int i = 1; i <= n; i++)
        insert(str[i] - 'a', i);
    for (int i = 1; i <= n; i++)
    {
        int p = 1;
        for (int j = i; j <= n; j++)
        {
            p = nodes[p].ch[str[j] - 'a'];
            pos[i][j] = p;
        }
    }

    stringSort();
    for (int i = 1; i <= n; i++)
    {
        dp[i] = dp[i - 1] + ca;
        for (int j = 1; j <= i - 1; j++)
            if (nodes[pos[j + 1][i]].occur <= j)
            {
                dp[i] = min(dp[i], dp[j] + cb);
                break;
            }
    }
    printf("%d", dp[n]);
    return 0;
}
