// P3966.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

int ch[MAX_N][26], fail[MAX_N], siz[MAX_N], n, pos[MAX_N], ptot, perm[MAX_N], permtot;
char opt[MAX_N];

void insert(int id, char *str)
{
    int p = 0;
    for (int i = 1; str[i] != '\0'; i++)
    {
        int digit = str[i] - 'a';
        if (ch[p][digit] == 0)
            ch[p][digit] = ++ptot;
        p = ch[p][digit], siz[p]++;
    }
    pos[id] = p;
}

void build_automaton()
{
    queue<int> q;
    for (int i = 0; i < 26; i++)
        if (ch[0][i] != 0)
            q.push(ch[0][i]), fail[ch[0][i]] = 0;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        perm[++permtot] = u;
        for (int i = 0; i < 26; i++)
            if (ch[u][i] != 0)
                fail[ch[u][i]] = ch[fail[u]][i], q.push(ch[u][i]);
            else
                ch[u][i] = ch[fail[u]][i];
    }
}

int main()
{
    scanf("%d", &n), siz[0] = 1;
    for (int i = 1; i <= n; i++)
        scanf("%s", opt + 1), insert(i, opt);
    build_automaton();
    for (int i = permtot; i >= 1; i--)
        siz[fail[perm[i]]] += siz[perm[i]];
    for (int i = 1; i <= n; i++)
        printf("%d\n", siz[pos[i]]);
    return 0;
}