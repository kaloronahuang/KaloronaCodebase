// P2444.cpp
#include <iostream>
#include <queue>
#include <cmath>
#include <cstring>
#include <cstdio>
using namespace std;
const int MX_N = 30020;
struct node
{
    node *nxt[2], *fail;
    bool sum, ins, vis;
    node() { nxt[0] = nxt[1] = fail = NULL, sum = 0, ins = vis = false; }
};
node *root;
int n, longest;
void insert(string str)
{
    int siz = str.length();
    node *p = root;
    for (int i = 0; i < siz; i++)
        p = (p->nxt[str[i] - '0'] == NULL) ? (p->nxt[str[i] - '0'] = new node()) : p->nxt[str[i] - '0'];
    p->sum = true;
}
void build_ac_automation()
{
    queue<node *> q;
    q.push(root);
    while (!q.empty())
    {
        node *curt = q.front();
        q.pop();
        for (int i = 0; i < 2; i++)
            if (curt->nxt[i] != NULL)
            {
                if (curt == root)
                    curt->nxt[i]->fail = root;
                else
                {
                    node *p = curt->fail;
                    while (p)
                        if (p->nxt[i] != NULL)
                        {
                            curt->nxt[i]->fail = p->nxt[i];
                            curt->nxt[i]->sum |= p->nxt[i]->sum;
                            break;
                        }
                        else
                            p = p->fail;
                    if (p == NULL)
                        curt->nxt[i]->fail = root;
                }
                q.push(curt->nxt[i]);
            }
            else if (curt->fail != NULL)
                curt->nxt[i] = curt->fail->nxt[i];
    }
}
bool dfs(node *curt)
{
    if (curt->ins)
        return true;
    if (curt->vis || curt->sum > 0)
        return false;
    curt->vis = curt->ins = true;
    for (int i = 0; i < 2; i++)
        if (curt->nxt[i] != NULL && dfs(curt->nxt[i]))
            return true;
    curt->ins = false;
    return false;
}
char buff[30020];
int main()
{
    scanf("%d", &n);
    root = new node();
    for (int i = 1; i <= n; i++)
        scanf("%s", buff), insert(buff);
    build_ac_automation();
    if (dfs(root))
        printf("TAK");
    else
        printf("NIE");
    return 0;
}