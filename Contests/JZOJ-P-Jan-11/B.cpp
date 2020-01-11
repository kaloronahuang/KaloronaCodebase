// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e6 + 200;

int n, ch[MAX_N][2], ptot = 1, head[MAX_N << 2], current, sat_tot = 1, dfn[MAX_N << 2], dtot;
int low[MAX_N << 2], aff[MAX_N << 2], stk[MAX_N << 2], tail, ncnt;
bool inst[MAX_N << 2];
int tag[MAX_N];
string str;
vector<string> strVec;

bool compare(string &a, string &b) { return a.length() < b.length(); }

void fileIO()
{
    freopen("code.in", "r", stdin);
    freopen("code.out", "w", stdout);
}

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void insert(int id)
{
    int p = 1, fa = 0;
    for (int i = 0; i < str.length(); i++)
    {
        if (ch[p][str[i] - '0'] == 0)
            ch[p][str[i] - '0'] = ++ptot;
        p = ch[p][str[i] - '0'];
        if (tag[p])
            fa = tag[p];
    }
    sat_tot += 2, addpath(id, sat_tot), addpath(sat_tot ^ 1, id ^ 1);
    if (fa)
    {
        addpath(fa, sat_tot), addpath(sat_tot ^ 1, fa ^ 1);
        addpath(fa, id ^ 1), addpath(id, fa ^ 1);
    }
    tag[p] = sat_tot;
}

void tarjan(int u)
{
    dfn[u] = low[u] = ++dtot, inst[u] = true, stk[++tail] = u;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (dfn[edges[i].to] == 0)
            tarjan(edges[i].to), low[u] = min(low[u], low[edges[i].to]);
        else if (inst[edges[i].to])
            low[u] = min(low[u], dfn[edges[i].to]);
    if (dfn[u] == low[u])
    {
        ncnt++;
        do
        {
            aff[stk[tail]] = ncnt, inst[stk[tail]] = false;
        } while (stk[tail--] != u);
    }
}

int main()
{
    fileIO();
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        cin >> str, strVec.push_back(str);
    sort(strVec.begin(), strVec.end(), compare);
    for (int i = 1; i <= n; i++)
    {
        bool flag = false;
        str = strVec[i - 1], sat_tot += 2;
        int pt = sat_tot;
        for (int ptr = 0; ptr < str.length(); ptr++)
            if (str[ptr] == '?')
            {
                flag = true;
                str[ptr] = '0', insert(pt - 1);
                str[ptr] = '1', insert(pt);
                break;
            }
        if (!flag)
            insert(pt), addpath(pt - 1, pt);
    }

    for (int i = 2; i <= sat_tot; i++)
        if (dfn[i] == 0)
            tarjan(i);
    for (int i = 2; i <= sat_tot; i += 2)
        if (aff[i] == aff[i + 1])
            puts("NO"), exit(0);
    puts("YES");
    return 0;
}