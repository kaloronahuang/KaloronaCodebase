// P3121.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, nodes[MAX_N][26], ptot, stk[MAX_N], tag[MAX_N], top, fail[MAX_N];
char passage[MAX_N], opt[MAX_N], cstk[MAX_N];

void insert(char *str)
{
    int p = 0;
    for (int i = 1; str[i] != '\0'; i++)
    {
        if (nodes[p][str[i] - 'a'] == 0)
            nodes[p][str[i] - 'a'] = ++ptot;
        p = nodes[p][str[i] - 'a'];
    }
    tag[p] = strlen(str + 1);
}

void build_automaton()
{
    queue<int> q;
    for (int i = 0; i < 26; i++)
        if (nodes[0][i] != 0)
            q.push(nodes[0][i]), fail[nodes[0][i]] = 0;
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

int main()
{
    scanf("%s%d", passage + 1, &n);
    for (int i = 1; i <= n; i++)
        scanf("%s", opt + 1), insert(opt);
    build_automaton();
    for (int i = 1, p = 0; passage[i] != '\0'; i++)
    {
        p = nodes[p][passage[i] - 'a'], stk[++top] = p, cstk[top] = passage[i];
        if (tag[p])
        {
            top -= tag[p];
            if (top == 0)
                p = 0;
            else
                p = stk[top];
        }
    }
    for (int i = 1; i <= top; i++)
        putchar(cstk[i]);
    putchar('\n');
    return 0;
}