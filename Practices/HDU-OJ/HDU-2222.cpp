// HDU-2222.cpp
#include <iostream>
#include <queue>
#include <cstdio>
#include <cstring>
using namespace std;
struct node
{
    node *nxt[26], *fail;
    int sum;
    ~node()
    {
        for (int i = 0; i < 26; i++)
            if (nxt[i] != NULL)
                delete nxt[i];
    }
};
node *root;
int cnt;
char str[1000020];
void insert(string str)
{
    int siz = str.length();
    node *p = root;
    for (int i = 0; i < siz; i++)
    {
        int curt = str[i] - 'a';
        if (p->nxt[curt] == NULL)
        {
            p->nxt[curt] = new node();
            p->nxt[curt]->fail = NULL;
            for (int i = 0; i < 26; i++)
                p->nxt[curt]->nxt[i] = NULL;
            p->nxt[curt]->sum = 0;
        }
        p = p->nxt[curt];
    }
    p->sum++;
}
void build_AC_automation()
{
    queue<node *> q;
    q.push(root);
    node *p, *tmp;
    while (!q.empty())
    {
        tmp = q.front();
        q.pop();
        for (int i = 0; i < 26; i++)
            if (tmp->nxt[i])
            {
                if (tmp == root)
                    tmp->nxt[i]->fail = root;
                else
                {
                    p = tmp->fail;
                    while (p)
                        if (p->nxt[i])
                        {
                            tmp->nxt[i]->fail = p->nxt[i];
                            break;
                        }
                        else
                            p = p->fail;
                    if (p == NULL)
                        tmp->nxt[i]->fail = root;
                }
                q.push(tmp->nxt[i]);
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
            if (tmp->sum >= 0)
            {
                cnt += tmp->sum;
                tmp->sum = -1;
            }
            else
                break;
            tmp = tmp->fail;
        }
    }
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int n;
        scanf("%d", &n);
        root = new node();
        for (int i = 1; i <= n; i++)
            scanf("%s", str), insert(str);
        build_AC_automation();
        scanf("%s", str);
        ac_automation(str);
        printf("%d\n", cnt);
        cnt = 0;
    }
    return 0;
}