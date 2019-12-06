// P3808.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e6 + 200;

int nodes[MAX_N][26], tag[MAX_N], fail[MAX_N], ptot, n;
char opt[MAX_N];

void insert(char *str)
{
    int p = 0;
    for (int i = 1; str[i] != '\0'; i++)
    {
        int digit = str[i] - 'a';
        if (nodes[p][digit] == 0)
            nodes[p][digit] = ++ptot;
        p = nodes[p][digit];
    }
    tag[p]++;
}

void inti_automaton()
{
    queue<int> q;
    for (int i = 0; i < 26; i++)
        if (nodes[0][i] != 0)
            fail[nodes[0][i]] = 0, q.push(nodes[0][i]);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = 0; i < 26; i++)
            if (nodes[u][i] != 0)
                fail[nodes[u][i]] = nodes[fail[u]][i], q.push(nodes[u][i]);
            else
                nodes[u][i] = nodes[fail[u]][i];
    }
}

int query(char *str)
{
    int p = 0, ret = 0;
    for (int i = 1; str[i] != '\0'; i++)
    {
        p = nodes[p][str[i] - 'a'];
        for (int pt = p; pt != 0 && tag[pt] != -1; pt = fail[pt])
            ret += tag[pt], tag[pt] = -1;
    }
    return ret;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%s", opt + 1), insert(opt);
    inti_automaton();
    scanf("%s", opt + 1);
    printf("%d\n", query(opt));
    return 0;
}