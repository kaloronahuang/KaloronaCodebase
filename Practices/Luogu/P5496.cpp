// P5496.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

int n, last_ptr, ptot;
char str[MAX_N];

struct node
{
    int ch[26], dep, link, sum;
} nodes[MAX_N];

int jumpLink(int p, int pos)
{
    while (str[pos - nodes[p].dep - 1] != str[pos])
        p = nodes[p].link;
    return p;
}

void insert(int pos)
{
    int pre = jumpLink(last_ptr, pos);
    if (nodes[pre].ch[str[pos] - 'a'] == 0)
    {
        int p = ++ptot;
        nodes[p].dep = nodes[pre].dep + 2;
        nodes[p].link = nodes[jumpLink(nodes[pre].link, pos)].ch[str[pos] - 'a'];
        nodes[p].sum = nodes[nodes[p].link].sum + 1;
        nodes[pre].ch[str[pos] - 'a'] = p;
    }
    last_ptr = nodes[pre].ch[str[pos] - 'a'];
}

int main()
{
    scanf("%s", str + 1), n = strlen(str + 1), ptot = 1;
    nodes[1].dep = -1, nodes[0].link = 1;
    for (int i = 1, last_ans = 0; i <= n; i++)
    {
        str[i] = (str[i] - 97 + last_ans) % 26 + 97;
        insert(i), printf("%d ", last_ans = nodes[last_ptr].sum);
    }
    puts("");
    return 0;
}