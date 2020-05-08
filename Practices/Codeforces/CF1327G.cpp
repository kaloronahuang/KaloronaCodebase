// CF1327G.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 4e5 + 200, MAX_NODE = 2020, MAX_K = 15;

typedef pair<int, int> pii;
typedef long long ll;

int n, kind, ch[MAX_NODE][MAX_K], tag[MAX_NODE], fail[MAX_NODE], ptot;
ll dp[MAX_NODE][1 << MAX_K];
char org[MAX_N];
vector<int> splits;

void insert(char *str, int val)
{
    int p = 0;
    for (int i = 1; str[i]; i++)
    {
        if (ch[p][str[i] - 'a'] == 0)
            ch[p][str[i] - 'a'] = ++ptot;
        p = ch[p][str[i] - 'a'];
    }
    tag[p] += val;
}

void build()
{
    queue<int> q;
    for (int i = 0; i < MAX_K; i++)
        if (ch[0][i])
            q.push(ch[0][i]);
    while (!q.empty())
    {
        int u = q.front();
        q.pop(), tag[u] += tag[fail[u]];
        for (int i = 0; i < MAX_K; i++)
            if (ch[u][i])
                fail[ch[u][i]] = ch[fail[u]][i], q.push(ch[u][i]);
            else
                ch[u][i] = ch[fail[u]][i];
    }
}

int main()
{
    scanf("%d", &kind);
    for (int i = 1, val; i <= kind; i++)
        scanf("%s%d", org + 1, &val), insert(org, val);
    build(), scanf("%s", org + 1), n = strlen(org + 1);
    org[0] = org[n + 1] = '?';
    for (int i = 0; i <= n + 1; i++)
        if (org[i] == '?')
            splits.push_back(i);
    memset(dp, 0xcf, sizeof(dp));
    /*
    for (int i = 0, siz_1 = splits.size(); i < siz_1; i++)
        for (int stat = 0; stat < (1 << 14); stat++)
            if (__builtin_popcount(stat) == i)
                for (int start_pos = 0; start_pos <= ptot; start_pos++)
                    dp[start_pos][stat] = 0xcfcfcfcfcfcfcfcf;
    */
    dp[0][0] = 0;
    for (int i = 0, siz_1 = splits.size(); i < siz_1 - 1; i++)
    {
        for (int start_pos = 0; start_pos <= ptot; start_pos++)
        {
            int p = start_pos;
            ll sum = 0;
            for (int j = splits[i] + 1; j <= splits[i + 1] - 1; j++)
                p = ch[p][org[j] - 'a'], sum += tag[p];
            for (int stat = 0; stat < (1 << 14); stat++)
            {
                if (__builtin_popcount(stat) != i)
                    continue;
                int lft = 0, rig = 13;
                if (i + 1 == siz_1 - 1)
                    lft = 14, rig = 14;
                for (int j = lft; j <= rig; j++)
                    if (!(stat & (1 << j)))
                    {
                        int nxt = ch[p][j];
                        dp[nxt][stat | (1 << j)] = max(dp[nxt][stat | (1 << j)], dp[start_pos][stat] + sum + tag[nxt]);
                    }
            }
        }
    }
    ll ans = ll(0xcfcfcfcfcfcfcfcf);
    for (int stat = 0; stat < (1 << 15); stat++)
        if (__builtin_popcount(stat) == splits.size() - 1)
            for (int p = 0; p <= ptot; p++)
                ans = max(ans, dp[p][stat]);
    printf("%lld\n", ans);
    return 0;
}