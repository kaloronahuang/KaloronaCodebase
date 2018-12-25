// P3796.cpp
#include <iostream>
#include <map>
#include <queue>
#include <cstring>
#include <cstdio>
using namespace std;
const int MX_T = 160;
struct node
{
    node *nxt[26], *fail;
    int wordId;
    node()
    {
        for (int i = 0; i < 26; i++)
            nxt[i] = NULL;
        fail = NULL;
        wordId = -1;
    }
};
node *root;
int anses[MX_T], n;
char src[MX_T][80], str[(int)1e6 + 200];
void insert(string str, int id)
{
    int siz = str.length();
    node *p = root;
    for (int i = 0; i < siz; i++)
    {
        int curt = str[i] - 'a';
        p = (p->nxt[curt] == NULL) ? (p->nxt[curt] = new node()) : p->nxt[curt];
    }
    p->wordId = id;
}
void build_AC_automation()
{
    queue<node *> q;
    q.push(root);
    while (!q.empty())
    {
        node *curt = q.front();
        q.pop();
        for (int i = 0; i < 26; i++)
            if (curt->nxt[i] != NULL)
            {
                if (curt == root)
                    curt->nxt[i]->fail = root;
                else
                {
                    node *p = curt->fail;
                    while (p)
                        if (p->nxt[i])
                        {
                            curt->nxt[i]->fail = p->nxt[i];
                            break;
                        }
                        else
                            p = p->fail;
                    if (p == NULL)
                        curt->nxt[i]->fail = root;
                }
                q.push(curt->nxt[i]);
            }
    }
}
void ac_automation(string passage)
{
    int siz = passage.length();
    node *p = root;
    for (int i = 0; i < siz; i++)
    {
        int curt = passage[i] - 'a';
        while (!p->nxt[curt] && p != root)
            p = p->fail;
        p = p->nxt[curt];
        if (p == NULL)
            p = root;
        node *tmp = p;
        while (tmp != root)
        {
            if (tmp->wordId != -1)
                anses[tmp->wordId]++;
            tmp = tmp->fail;
        }
    }
}
int main()
{
    while (scanf("%d", &n) && n != 0)
    {
        memset(anses, 0, sizeof(anses));
        root = new node();
        for (int i = 1; i <= n; i++)
            scanf("%s", &src[i]), insert(src[i], i);
        scanf("%s", &str);
        build_AC_automation();
        ac_automation(str);
        int id = 0, val = 0;
        for (int i = 1; i <= n; i++)
            if (anses[i] > val)
                id = i, val = anses[i];
        printf("%d\n", val);
        for (int i = 1; i <= n; i++)
            if (anses[i] == val)
                printf("%s\n", src[i]);
    }
    return 0;
}