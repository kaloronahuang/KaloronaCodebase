// P1110.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 1000100;
int n, m, nxt[MAX_N], prv[MAX_N], val[MAX_N], tmpx, curs[MAX_N], ltot, min_gap = 0x3f3f3f3f;
multiset<int> ms, splay;
char opt[20];
void insert_list(int x, int d)
{
    int cursor = ++ltot;
    ms.erase(ms.lower_bound(abs(val[nxt[curs[d]]] - val[curs[d]])));
    nxt[cursor] = nxt[curs[d]], prv[cursor] = curs[d], val[cursor] = x;
    prv[nxt[curs[d]]] = ltot, nxt[curs[d]] = ltot;
    curs[d] = cursor;
    ms.insert(abs(val[prv[curs[d]]] - val[curs[d]])), ms.insert(abs(val[nxt[curs[d]]] - val[curs[d]]));
}
void update_set(int x)
{
    multiset<int>::iterator it = splay.lower_bound(x);
    int nw = abs(*it - x);
    nw = min(nw, abs(x - *(--it)));
    min_gap = min(min_gap, nw);
    splay.insert(x);
}
int main()
{
    scanf("%d%d", &n, &m);
    splay.insert(0x3f3f3f3f), splay.insert(-0x3f3f3f3f);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &tmpx);
        val[i] = tmpx, prv[i] = i - 1, nxt[i] = i + 1, curs[i] = i;
        if (i != 1)
            ms.insert(abs(val[i] - val[i - 1]));
        update_set(tmpx);
    }
    nxt[n] = 0, ltot = n;
    while (m--)
    {
        scanf("%s", opt + 1);
        if (opt[1] == 'I')
        {
            int x, d;
            scanf("%d%d", &d, &x);
            insert_list(x, d), update_set(x);
        }
        else if (opt[5] == 'S')
            printf("%d\n", min_gap);
        else
            printf("%d\n", *(ms.begin()));
    }
    return 0;
}