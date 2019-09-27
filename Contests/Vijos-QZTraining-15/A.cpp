// A.cpp
#include <bits/stdc++.h>
#define pr pair<int, int>

using namespace std;

const int MAX_N = 1010, MAX_P = 350100;

int cvt_ci[MAX_N];

int ch[MAX_P][4], ptot, root, tag[MAX_P], T;
bitset<MAX_N> vis[MAX_P];
queue<pr> q;
char txt[MAX_N], tmp[MAX_N];

void insert(const char str[])
{
    int len = strlen(str), p = root;
    for (int i = 0; i < len; i++)
    {
        if (ch[p][cvt_ci[str[i]]] == 0)
            ch[p][cvt_ci[str[i]]] = ++ptot;
        p = ch[p][cvt_ci[str[i]]];
    }
    tag[p]++;
}

void push_node(int u, int dep, int len)
{
    if (u == 0 || dep >= len || vis[u][dep] == 1)
        return;
    vis[u][dep] = 1, q.push(make_pair(u, dep));
}

int search(const char str[])
{
    int len = strlen(str), res = 0;
    q.push(make_pair(root, 0));
    vis[1][0] = 1;
    while (!q.empty())
    {
        int u = q.front().first, dep = q.front().second;
        q.pop();
        if (str[dep] == '*')
            for (int i = 0; i < 4; i++)
                push_node(ch[u][i], dep, len);
        if (dep + 1 == len)
        {
            res += (tag[u]--);
            continue;
        }
        int id = cvt_ci[str[dep + 1]];
        if (id >= 0)
            push_node(ch[u][id], dep + 1, len);
        else
        {
            for (int i = 0; i < 4; i++)
                push_node(ch[u][i], dep + 1, len);
            if (str[dep + 1] == '*')
                push_node(u, dep + 1, len);
        }
    }
    return res;
}

int main()
{
    root = ++ptot;
    cvt_ci['A'] = 0, cvt_ci['G'] = 1;
    cvt_ci['C'] = 2, cvt_ci['T'] = 3;
    cvt_ci['?'] = -1, cvt_ci['*'] = -2;
    scanf("%s", txt + 1), txt[0] = '?';
    scanf("%d", &T);
    for (int i = 1; i <= T; i++)
        scanf("%s", tmp), insert(tmp);
    printf("%d", T - search(txt));
    return 0;
}