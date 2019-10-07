// cellphone.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 2e5 + 200, INF = 0x7f7f7f7f;

struct node
{
    int l, r, v;
    bool operator<(const node &nd) const { return l < nd.l; }
} nodes[MAX_N];

set<node> S;
typedef set<node>::iterator SIT;
int q;
ll C;
char str[20];

int fromL(int l, int val, int r) { return l + ((r - l) / val) * val; }
int fromR(int r, int val, int l) { return r - ((r - l) / val) * val; }

void construct(int l, int r, int v)
{
    r = fromL(l, v, r);
    SIT it = S.upper_bound(node{l, 0, 0});
    if (it != S.begin())
    {
        it--;
        // split it up;
        if (it->l < l && r < it->r)
        {
            // into two unique intervals;
            node tmp = *it;
            S.erase(it);
            node lft = node{tmp.l, fromL(tmp.l, tmp.v, l), tmp.v};
            node rig = node{fromR(tmp.r, tmp.v, r), tmp.r, tmp.v};
            S.insert(lft), S.insert(rig);
        }
    }
    S.insert(node{l, r, v});
}

void destruct(int l, int r)
{
    SIT it = S.lower_bound(node{l, 0, 0});
    if (it != S.begin())
    {
        it--;
        if (it->l < l && l <= it->r)
        {
            node t = *it;
            S.erase(it);
            int rbound = fromL(t.l, t.v, l - 1);
            S.insert(node{t.l, rbound, t.v});
        }
    }
    it = S.upper_bound(node{r, 0, 0});
    if (it != S.begin())
    {
        it--;
        if (it->l <= r && r < it->r)
        {
            node t = *it;
            S.erase(it);
            int lbound = fromR(t.r, t.v, r + 1);
            S.insert(node{lbound, t.r, t.v});
        }
    }
    S.erase(S.lower_bound(node{l, 0, 0}), S.upper_bound(node{r, 0, 0}));
}

ll query(int x)
{
    SIT it = S.lower_bound(node{x, 0, 0});
    int ans = INF;
    if (it != S.end())
        ans = min(ans, abs(it->l - x));
    if (it != S.begin())
    {
        it--;
        if (it->r >= x)
        {
            int lft = fromL(it->l, it->v, x), rig = fromR(it->r, it->v, x);
            ans = min(ans, min(abs(x - lft), abs(rig - x)));
        }
        else
            ans = min(ans, abs(x - it->r));
    }
    if (ans >= INF)
        return 0;
    return max(0LL, C - 1LL * ans * ans);
}

int main()
{
    scanf("%d%lld", &q, &C);
    while (q--)
    {
        int l, r, v;
        scanf("%s", str + 1);
        if (str[1] == 'c')
            scanf("%d%d%d", &l, &r, &v), construct(l, r, v);
        else if (str[1] == 'd')
            scanf("%d%d", &l, &r), destruct(l, r);
        else
            scanf("%d", &v), printf("%lld\n", query(v));
    }
    return 0;
}