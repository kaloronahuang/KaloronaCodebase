// LOJ6401.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

typedef long long ll;

int n, limit, ptot = 1, last_ptr = 1, bucket[MAX_N], idx[MAX_N], pre[MAX_N], dp[MAX_N];
char str[MAX_N], opt[MAX_N];

struct node
{
    int ch[26], dep, link;
} nodes[MAX_N];

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
    scanf("%s%s%d", str + 1, opt + 1, &limit), n = strlen(str + 1);
    for (int i = 1, j = 0; i <= n; i++)
    {
        pre[i] = pre[i - 1] + (opt[i] == '0');
        while (pre[i] - pre[j] > limit)
            j++;
        insert(str[i] - 'a'), dp[last_ptr] = i - j;
    }
    for (int i = 1; i <= ptot; i++)
        bucket[nodes[i].dep]++;
    for (int i = 1; i <= ptot; i++)
        bucket[i] += bucket[i - 1];
    for (int i = 1; i <= ptot; i++)
        idx[bucket[nodes[i].dep]--] = i;
    ll ans = 0;
    for (int i = ptot; i >= 1; i--)
        if (nodes[idx[i]].link != 0)
        {
            ans += max(0, min(dp[idx[i]], nodes[idx[i]].dep) - nodes[nodes[idx[i]].link].dep);
            dp[nodes[idx[i]].link] = max(dp[nodes[idx[i]].link], dp[idx[i]]);
        }
    printf("%lld\n", ans);
    return 0;
}