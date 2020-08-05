// FOJ3226.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e4 + 200;

int n, ai[MAX_N], roots[MAX_N], ptot, idx[MAX_N];

struct node
{
    int ch[2], sum;
} nodes[MAX_N * 40];

int insert(int x, int dep, int pre)
{
    if (dep == -1)
        return 0;
    int c = (x >> dep) & 1, p = ++ptot;
    nodes[p] = nodes[pre], nodes[p].sum++;
    nodes[p].ch[c] = insert(x, dep - 1, nodes[pre].ch[c]);
    return p;
}

int getMaxVal(int x, int p, int pre)
{
    int ret = 0;
    for (int i = 30; i >= 0; i--)
    {
        int c = (x >> i) & 1;
        if (nodes[nodes[p].ch[!c]].sum - nodes[nodes[pre].ch[!c]].sum > 0)
            p = nodes[p].ch[!c], pre = nodes[pre].ch[!c], ret += (1 << i);
        else
            p = nodes[p].ch[c], pre = nodes[pre].ch[c];
    }
    return ret;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]), roots[i] = insert(ai[i], 30, roots[i - 1]), idx[i] = i;
    sort(idx + 1, idx + 1 + n, [](const int &rhs1, const int &rhs2) { return ai[rhs1] < ai[rhs2]; });
    reverse(idx + 1, idx + 1 + n);
    set<int> pos_set;
    pos_set.insert(idx[1]);
    int ans = 0;
    for (int i = 2; i <= n; i++)
    {
        set<int>::iterator curt_pos = pos_set.insert(idx[i]).first;
        int lft, rig;
        // process the lft;
        if (curt_pos == pos_set.begin())
            lft = 1;
        else
        {
            curt_pos--;
            if (curt_pos == pos_set.begin())
                lft = 1;
            else
                curt_pos--, lft = *curt_pos + 1, curt_pos++;
            curt_pos++;
        }
        // process the rig;
        curt_pos++;
        if (curt_pos == pos_set.end())
            rig = n;
        else
        {
            curt_pos++;
            if (curt_pos == pos_set.end())
                rig = n;
            else
                rig = *curt_pos - 1;
        }
        ans = max(ans, getMaxVal(ai[idx[i]], roots[rig], roots[lft - 1]));
    }
    printf("%d\n", ans + 1);
    return 0;
}