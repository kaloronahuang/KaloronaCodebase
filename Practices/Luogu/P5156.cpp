// P5156.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

typedef long long ll;

int n, ai[MAX_N], head[MAX_N], current;
ll k;
bool tag[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N];

struct node
{
    int val;
    ll sum;
} nodes[MAX_N], dp[MAX_N];

inline int lowbit(int x) { return x & (-x); }

node merge(node a, node b)
{
    if (a.val < b.val)
        swap(a, b);
    if (a.val == b.val)
        a.sum = min(a.sum + b.sum, ll(1e18));
    return a;
}

void update(int x, node d)
{
    for (; x; x -= lowbit(x))
        nodes[x] = merge(nodes[x], d);
}

node query(int x)
{
    node ret = node{0, 0};
    for (; x <= n + 1; x += lowbit(x))
        ret = merge(nodes[x], ret);
    return ret;
}

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%lld", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    update(n + 1, node{0, 1});
    for (int i = n; i >= 1; i--)
    {
        node tmp = query(ai[i] + 1);
        update(ai[i], dp[i] = node{tmp.val + 1, tmp.sum});
        addpath(dp[i].val, i);
    }
    for (int len = query(1).val, ptr = 0; len; len--)
        for (int i = head[len]; i != -1; i = edges[i].nxt)
        {
            if (k > dp[edges[i].to].sum)
                k -= dp[edges[i].to].sum;
            else
            {
                tag[ai[edges[i].to]] = true;
                while (ptr < edges[i].to)
                    dp[ptr++] = node{0, 0};
                break;
            }
        }
    printf("%d\n", n - query(1).val);
    for (int i = 1; i <= n; i++)
        if (!tag[i])
            printf("%d\n", i);
    return 0;
}