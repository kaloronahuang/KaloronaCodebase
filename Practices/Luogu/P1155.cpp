// P1155.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2020;

int seq[MAX_N], n, suf[MAX_N], color[MAX_N], pos = 1;
vector<int> G[MAX_N];
stack<int> st[2];

bool pop_stack(int id)
{
    if (!st[id].empty() && st[id].top() == pos)
    {
        st[id].pop(), pos++, printf("%c ", id == 0 ? 'b' : 'd');
        return true;
    }
    return false;
}

void push_stack(int ele, int id)
{
    if (id == 1)
        while (pop_stack(0))
            ;
    while (!st[id].empty() && st[id].top() < ele)
        if (!pop_stack(id))
            pop_stack(id ^ 1);
    if (id == 1)
        while (pop_stack(0))
            ;
    st[id].push(ele), printf("%c ", id == 0 ? 'a' : 'c');
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &seq[i]);
    suf[n + 1] = n + 1;
    for (int i = n; i >= 1; i--)
        suf[i] = min(suf[i + 1], seq[i]);
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            if (suf[j + 1] < seq[i] && seq[i] < seq[j])
                G[i].push_back(j), G[j].push_back(i), color[i] = color[j] = -1;
    for (int i = 1; i <= n; i++)
        if (color[i] == -1)
        {
            queue<int> q;
            q.push(i), color[i] = 0;
            while (!q.empty())
            {
                int u = q.front();
                q.pop();
                for (int j = 0, siz = G[u].size(); j < siz; j++)
                {
                    if (color[G[u][j]] != -1 && (color[G[u][j]] ^ color[u]) != 1)
                        puts("0"), exit(0);
                    if (color[G[u][j]] == -1)
                        q.push(G[u][j]);
                    color[G[u][j]] = color[u] ^ 1;
                }
            }
        }
    for (int i = 1; i <= n; i++)
        push_stack(seq[i], color[i]);
    bool flag = true;
    while (flag)
    {
        flag = false;
        while (pop_stack(0))
            flag = true;
        while (pop_stack(1))
            flag = true;
    }
    return 0;
}