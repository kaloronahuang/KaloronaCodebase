// TWOSTRS.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

typedef long long ll;

int T, n, na, nb, ptot;
ll suf[MAX_N];
char sA[MAX_N], sB[MAX_N], tmp[MAX_N];

struct node
{
    int ch[26], link;
    ll valsum;
} nodes[MAX_N << 1];

void insert(char *str, int price)
{
    int p = 0;
    for (int i = 1; str[i]; i++)
    {
        if (nodes[p].ch[str[i] - 'a'] == 0)
            nodes[p].ch[str[i] - 'a'] = ++ptot;
        p = nodes[p].ch[str[i] - 'a'];
    }
    nodes[p].valsum += price;
}

void build()
{
    queue<int> q;
    for (int i = 0; i < 26; i++)
        if (nodes[0].ch[i])
            q.push(nodes[0].ch[i]);
    while (!q.empty())
    {
        int u = q.front();
        q.pop(), nodes[u].valsum += nodes[nodes[u].link].valsum;
        for (int i = 0; i < 26; i++)
            if (nodes[u].ch[i] == 0)
                nodes[u].ch[i] = nodes[nodes[u].link].ch[i];
            else
            {
                nodes[nodes[u].ch[i]].link = nodes[nodes[u].link].ch[i];
                q.push(nodes[u].ch[i]);
            }
    }
}

void calcSuffix()
{
    for (int i = 1, p = 0; i <= nb; i++)
        p = nodes[p].ch[sB[i] - 'a'], suf[i] = nodes[p].valsum;
    suf[nb + 1] = 0;
    for (int i = nb; i >= 1; i--)
        suf[i] += suf[i + 1];
}

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        for (int i = 0; i <= ptot; i++)
        {
            memset(nodes[i].ch, 0, sizeof(nodes[i].ch));
            nodes[i].link = nodes[i].valsum = 0;
        }
        ptot = 0, scanf("%s%s%d", sA + 1, sB + 1, &n);
        na = strlen(sA + 1), nb = strlen(sB + 1);
        for (int i = 1, bi; i <= n; i++)
            scanf("%s%d", tmp + 1, &bi), insert(tmp, bi);
        build(), calcSuffix();
        ll ans = 0, pre = 0;
        for (int i = 1, p = 0; i <= na; i++)
        {
            p = nodes[p].ch[sA[i] - 'a'], pre += nodes[p].valsum;
            for (int j = 1; j <= nb; j++)
            {
                int cp = p;
                ll acc = pre;
                for (int k = 0; k < 26 && j + k <= nb; k++)
                {
                    int pos = j + k;
                    cp = nodes[cp].ch[sB[pos] - 'a'];
                    acc += nodes[cp].valsum;
                }
                if (j + 26 <= nb)
                    acc += suf[j + 26];
                ans = max(ans, acc);
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}