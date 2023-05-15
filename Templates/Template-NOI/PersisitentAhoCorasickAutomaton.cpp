// PersisitentAhoCorasickAutomaton.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int n, ch[MAX_N][26], ptot, link[MAX_N], tag[MAX_N], stk[MAX_N], tail;
char org[MAX_N], tmp[MAX_N], cstk[MAX_N];

void insert(char *str)
{
    int p = 0;
    for (int i = 1; str[i]; i++)
    {
        if (ch[p][str[i] - 'a'] == 0)
            ch[p][str[i] - 'a'] = ++ptot;
        p = ch[p][str[i] - 'a'];
    }
    tag[p] = strlen(str + 1);
}

void build()
{
    queue<int> q;
    for (int i = 0; i < 26; i++)
        if (ch[0][i])
            q.push(ch[0][i]);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = 0; i < 26; i++)
            if (ch[u][i])
                link[ch[u][i]] = ch[link[u]][i], q.push(ch[u][i]);
            else
                ch[u][i] = ch[link[u]][i];
    }
}

int main()
{
    scanf("%s%d", org + 1, &n);
    for (int i = 1; i <= n; i++)
        scanf("%s", tmp + 1), insert(tmp);
    build();
    int p = 0;
    for (int i = 1; org[i]; i++)
    {
        p = ch[p][org[i] - 'a'], stk[++tail] = p, cstk[tail] = org[i];
        if (tag[p])
            tail -= tag[p];
        if (tail == 0)
            p = 0;
        else
            p = stk[tail];
    }
    for (int i = 1; i <= tail; i++)
        putchar(cstk[i]);
    puts("");
    return 0;
}