// P4735.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 600100;

int roots[MAX_N * 28], ptot = 1, ch[MAX_N * 28][2], tag[MAX_N * 28], prefix[MAX_N], n, m, tmp, tmpl, tmpr;

void insert(int p, int num, int bit, int pre)
{
    if (bit < 0)
        return;
    int i = (num >> bit) & 1;
    ch[p][!i] = ch[pre][!i];
    ch[p][i] = ptot++;
    tag[ch[p][i]] = tag[ch[pre][i]] + 1;
    insert(ch[p][i], num, bit - 1, ch[pre][i]);
}

int query(int lft, int rig, int bit, int num)
{
    if (bit < 0)
        return 0;
    int b = (num >> bit) & 1;
    if (tag[ch[rig][!b]] > tag[ch[lft][!b]])
        return (1 << bit) | query(ch[lft][!b], ch[rig][!b], bit - 1, num);
    else
        return query(ch[lft][b], ch[rig][b], bit - 1, num);
}

int main()
{
    scanf("%d%d", &n, &m);
    char opt[3];
    roots[0] = ptot++;
    insert(roots[0], 0, 26, 0);
    for (int i = 1; i <= n; i++)
        scanf("%d", &prefix[i]), prefix[i] ^= prefix[i - 1], roots[i] = ptot++, insert(roots[i], prefix[i], 26, roots[i - 1]);
    while (m--)
    {
        scanf("%s", opt + 1);
        if (opt[1] == 'A')
        {
            scanf("%d", &tmp), n++, prefix[n] = prefix[n - 1] ^ tmp;
            roots[n] = ptot++;
            insert(roots[n], prefix[n], 26, roots[n - 1]);
        }
        else
        {
            scanf("%d%d%d", &tmpl, &tmpr, &tmp), tmpl--, tmpr--;
            if (tmpl == 0)
                printf("%d\n", query(0, roots[tmpr], 26, prefix[n] ^ tmp));
            else
                printf("%d\n", query(roots[tmpl - 1], roots[tmpr], 26, prefix[n] ^ tmp));
        }
    }
    return 0;
}