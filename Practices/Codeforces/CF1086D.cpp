// CF1086D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int n, q, nodes[3][MAX_N];
char str[MAX_N];
set<int> container[3];

int lowbit(int x) { return x & (-x); }

void update(int id, int x, int d)
{
    for (; x <= n; x += lowbit(x))
        nodes[id][x] += d;
}

int query(int id, int x, int ret = 0)
{
    for (; x; x -= lowbit(x))
        ret += nodes[id][x];
    return ret;
}

int queryInterval(int id, int l, int r) { return l > r ? 0 : query(id, r) - query(id, l - 1); }

int decode(char ch) { return ch == 'R' ? 0 : (ch == 'P' ? 1 : 2); }

void insert(int pos, char typ, int val)
{
    int c = decode(typ);
    update(c, pos, val);
    if (val == -1)
        container[c].erase(pos);
    else
        container[c].insert(pos);
}

int calc()
{
    int ret = n;
    for (int i = 0; i < 3; i++)
    {
        int l1, r1, l2, r2;
        set<int>::iterator it = container[(i + 1) % 3].begin();
        if (it == container[(i + 1) % 3].end())
            l1 = n + 1;
        else
            l1 = *it;
        it = container[(i + 1) % 3].end();
        if (it == container[(i + 1) % 3].begin())
            r2 = 0;
        else
            it--, r2 = *it;

        it = container[(i + 2) % 3].begin();
        if (it == container[(i + 2) % 3].end())
            r1 = n;
        else
            r1 = *it;
        it = container[(i + 2) % 3].end();
        if (it == container[(i + 2) % 3].begin())
            l2 = 1;
        else
            it--, l2 = *it;
        ret -= queryInterval(i, l1, r1) + queryInterval(i, l2, r2);
        ret += queryInterval(i, max(l1, l2), min(r1, r2));
    }
    return ret;
}

int main()
{
    scanf("%d%d%s", &n, &q, str + 1);
    for (int i = 1; i <= n; i++)
        insert(i, str[i], 1);
    printf("%d\n", calc());
    while (q--)
    {
        int pos;
        char cmdlet[10];
        scanf("%d%s", &pos, cmdlet + 1);
        insert(pos, str[pos], -1), str[pos] = cmdlet[1], insert(pos, str[pos], 1);
        printf("%d\n", calc());
    }
    return 0;
}