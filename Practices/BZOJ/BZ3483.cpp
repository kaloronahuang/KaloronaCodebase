// BZ3483.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2010, MAX_L = 2001000;

typedef pair<int, int> pii;

int n, q, lastans, descreteMap[MAX_N][MAX_N];
char tmp[MAX_L];

struct Trie
{
    int ch[MAX_L][26], ptot = 1, tag[MAX_L], lft[MAX_L], rig[MAX_L], dtot, pos[MAX_L];

    void insert(char *str, int idx)
    {
        int p = 1;
        for (int i = 1; str[i]; i++)
        {
            if (ch[p][str[i] - 'a'] == 0)
                ch[p][str[i] - 'a'] = ++ptot;
            p = ch[p][str[i] - 'a'];
        }
        tag[p] = idx;
    }

    void dfs(int u)
    {
        lft[u] = tag[u] ? ++dtot : 0x3f3f3f3f;
        rig[u] = tag[u] ? dtot : -0x3f3f3f3f;
        for (int i = 0; i < 26; i++)
            if (ch[u][i])
                dfs(ch[u][i]), lft[u] = min(lft[u], lft[ch[u][i]]), rig[u] = max(rig[u], rig[ch[u][i]]);
        if (tag[u])
            pos[tag[u]] = lft[u];
    }
} tr[2];

void decode()
{
    for (int i = 1; tmp[i]; i++)
        tmp[i] = (tmp[i] - 'a' + lastans) % 26 + 'a';
}

int main()
{
    scanf("%d", &n), tr[0].ptot = tr[1].ptot = 1;
    for (int i = 1; i <= n; i++)
    {
        scanf("%s", tmp + 1);
        tr[0].insert(tmp, i), reverse(tmp + 1, tmp + 1 + strlen(tmp + 1)), tr[1].insert(tmp, i);
    }
    tr[0].dfs(1), tr[1].dfs(1);
    for (int i = 1; i <= n; i++)
        descreteMap[tr[0].pos[i]][tr[1].pos[i]]++;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            descreteMap[i][j] += descreteMap[i - 1][j] + descreteMap[i][j - 1] - descreteMap[i - 1][j - 1];
    scanf("%d", &q);
    while (q--)
    {
        scanf("%s", tmp + 1), decode();
        int l1, r1, l2, r2, p = 1;
        for (int i = 1; tmp[i]; i++)
            p = tr[0].ch[p][tmp[i] - 'a'];
        l1 = tr[0].lft[p], r1 = tr[0].rig[p];
        scanf("%s", tmp + 1), decode(), p = 1, reverse(tmp + 1, tmp + 1 + strlen(tmp + 1));
        for (int i = 1; tmp[i]; i++)
            p = tr[1].ch[p][tmp[i] - 'a'];
        l2 = tr[1].lft[p], r2 = tr[1].rig[p];
        if (min(l1, min(r1, min(l2, r2))) == 0)
            puts("0"), lastans = 0;
        else
            printf("%d\n", lastans = descreteMap[r1][r2] - descreteMap[l1 - 1][r2] - descreteMap[r1][l2 - 1] + descreteMap[l1 - 1][l2 - 1]);
    }
    return 0;
}