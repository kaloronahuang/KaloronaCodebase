// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e6 + 200;

typedef long long ll;

int q, typ, ptot, mtot, limit[1010], lg[MAX_N << 2];
char org[MAX_N];
ll lans;

struct node
{
    int ch[26], link, val, bval;
} nodes[MAX_N << 2];

struct DFA
{
    int root, siz;

    ll query(char *str)
    {
        ll ret = 0, p = root;
        for (int i = 1; str[i]; i++)
        {
            while (p != root && nodes[p].ch[str[i] - 'a'] == 0)
                p = nodes[p].link;
            if (nodes[p].ch[str[i] - 'a'])
                p = nodes[p].ch[str[i] - 'a'], ret += nodes[p].val;
        }
        return ret;
    }

    void insert(char *str, int weight)
    {
        int p = root;
        for (int i = 1; str[i]; i++)
        {
            if (nodes[p].ch[str[i] - 'a'] == 0)
                nodes[p].ch[str[i] - 'a'] = ++ptot;
            p = nodes[p].ch[str[i] - 'a'], siz++;
        }
        nodes[p].val += weight, nodes[p].bval += weight;
    }

    void build()
    {
        queue<int> q;
        for (int i = 0; i < 26; i++)
            if (nodes[root].ch[i])
                q.push(nodes[root].ch[i]), nodes[nodes[root].ch[i]].link = root;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (int i = 0; i < 26; i++)
                if (nodes[u].ch[i])
                {
                    int v = nodes[u].ch[i], pre = nodes[u].link;
                    while (pre != root && nodes[pre].ch[i] == 0)
                        pre = nodes[pre].link;
                    if (nodes[pre].ch[i] != 0)
                        nodes[v].link = nodes[pre].ch[i], nodes[v].val += nodes[nodes[v].link].val;
                    else
                        nodes[v].link = root;
                    q.push(v);
                }
        }
    }
} machines[1010];

void collect(int ua)
{
    nodes[ua].val = nodes[ua].bval;
    for (int i = 0; i < 26; i++)
        if (nodes[ua].ch[i])
            collect(nodes[ua].ch[i]);
}

void dfs(int ua, int ub)
{
    if (ua != ub)
        nodes[ua].bval += nodes[ub].bval;
    for (int i = 0; i < 26; i++)
        if (nodes[ub].ch[i] != 0)
        {
            if (nodes[ua].ch[i] == 0)
            {
                nodes[ua].ch[i] = nodes[ub].ch[i];
                continue;
            }
            dfs(nodes[ua].ch[i], nodes[ub].ch[i]);
        }
}

void merge(DFA &src, DFA &dst) { src.siz += dst.siz, dfs(src.root, dst.root), collect(src.root), src.build(); }

void insert(char *str, int val)
{
    machines[mtot].insert(str, val);
    machines[mtot].build(), limit[mtot] = lg[machines[mtot].siz];
    while (mtot > 1 && limit[mtot] >= limit[mtot - 1])
    {
        merge(machines[mtot - 1], machines[mtot]);
        mtot--, limit[mtot] = lg[machines[mtot].siz];
    }
    machines[++mtot].root = ++ptot, machines[mtot].siz = limit[mtot] = 0;
}

ll query(char *str)
{
    ll ret = 0;
    for (int i = 1; i <= mtot; i++)
        ret += machines[i].query(str);
    return ret;
}

void initialize()
{
    machines[++mtot].root = ++ptot;
    for (int i = 2; i < (MAX_N << 2); i++)
        lg[i] = lg[i >> 1] + 1;
}

void decode(char *str)
{
    for (int i = 1; str[i]; i++)
        str[i] = (ll(str[i] - 'a') ^ lans) % 26 + 'a';
}

int main()
{
    initialize(), scanf("%d%d", &q, &typ);
    while (q--)
    {
        int opt, x;
        scanf("%d%s", &opt, org + 1);
        if (typ)
            decode(org);
        if (opt == 0)
            scanf("%d", &x), insert(org, x);
        else
            printf("%lld\n", lans = query(org));
    }
    return 0;
}