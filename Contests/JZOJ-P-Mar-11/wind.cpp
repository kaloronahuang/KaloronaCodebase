// wind.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

typedef pair<int, int> pii;

int n, m, ci[MAX_N], q;
bool orient[MAX_N];
char cmdlet[10];
/*
namespace Subtask1
{

int mat[110][110];

void subtask1Handler()
{
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= ci[i]; j++)
            mat[i][j] = 1;
    while (q--)
    {
        int x, y, ret = 0;
        scanf("%s", cmdlet + 1);
        if (cmdlet[1] == 'a')
            scanf("%d%d", &x, &y), mat[x][y]++;
        else if (cmdlet[1] == 'd')
            scanf("%d%d", &x, &y), mat[x][y]--;
        else if (cmdlet[1] == 'q')
        {
            scanf("%d%d", &x, &y);
            int opt = cmdlet[2] == 'u' ? -1 : 1;
            while (x >= 1 && x <= n && mat[x][y] == 1)
                ret++, x += opt;
            printf("%d\n", ret);
        }
        else
            for (int i = 1; i <= n; i++)
            {
                sort(mat[i] + 1, mat[i] + 1 + m);
                if (cmdlet[1] == 'l')
                    reverse(mat[i] + 1, mat[i] + 1 + m);
            }
    }
}

} // namespace Subtask1
*/
namespace Subtask2
{

void subtask2Handler()
{
    int x, y, ret = 0;
    scanf("%s", cmdlet + 1);
    if (cmdlet[1] == 'q')
    {
        scanf("%d%d", &x, &y);
        int opt = cmdlet[2] == 'u' ? -1 : 1;
        while (x >= 1 && x <= n && y <= ci[x])
            ret++, x += opt;
        printf("%d\n", ret);
    }
}

} // namespace Subtask2

namespace Subtask3
{

set<pii> segs[1100];

bool operator<(const pii &A, const pii &B) { return A.first < B.first; }

void subtask3Handler()
{
    for (int i = 1; i <= n; i++)
        segs[i].insert(make_pair(1, ci[i]));
    while (q--)
    {
        int x, y, ret = 0;
        scanf("%s", cmdlet + 1);
        if (cmdlet[1] == 'a')
        {
            scanf("%d%d", &x, &y);
            segs[x].insert(make_pair(y, y));
            ci[x]++;
        }
        else if (cmdlet[1] == 'd')
        {
            scanf("%d%d", &x, &y);
            set<pii>::iterator it = --segs[x].upper_bound(make_pair(y, y));
            segs[x].erase(it);
            pii pre = make_pair(it->first, y - 1), succ = make_pair(y + 1, it->second);
            if (pre.first <= pre.second)
                segs[x].insert(pre);
            if (succ.first <= succ.second)
                segs[x].insert(succ);
            ci[x]--;
        }
        else if (cmdlet[1] == 'q')
        {
            scanf("%d%d", &x, &y);
            int opt = cmdlet[2] == 'u' ? -1 : 1;
            while (x >= 1 && x <= n)
            {
                set<pii>::iterator it = --segs[x].upper_bound(make_pair(y, y));
                if (it == segs[x].end() || it->second < y || it->first > y)
                    break;
                ret++, x += opt;
            }
            printf("%d\n", ret);
        }
        else
            for (int i = 1; i <= n; i++)
            {
                segs[i].clear();
                if (cmdlet[1] == 'l')
                    segs[i].insert(make_pair(1, ci[i]));
                else
                    segs[i].insert(make_pair(m - ci[i] + 1, m));
            }
    }
}

} // namespace Subtask3

namespace Subtask4
{

struct node
{
    int min_val, max_val, tag_add, revTag;
} nodes[MAX_N << 2];

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

void pushdown(int p)
{
    nodes[lson].max_val = nodes[lson].max_val * nodes[p].revTag + nodes[p].tag_add;
    nodes[lson].min_val = nodes[lson].min_val * nodes[p].revTag + nodes[p].tag_add;
    if (nodes[lson].min_val > nodes[lson].max_val)
        swap(nodes[lson].min_val, nodes[lson].max_val);

    nodes[rson].max_val = nodes[rson].max_val * nodes[p].revTag + nodes[p].tag_add;
    nodes[rson].min_val = nodes[rson].min_val * nodes[p].revTag + nodes[p].tag_add;
    if (nodes[rson].min_val > nodes[rson].max_val)
        swap(nodes[rson].min_val, nodes[rson].max_val);

    nodes[lson].revTag *= nodes[p].revTag, nodes[rson].revTag *= nodes[p].revTag;

    nodes[lson].tag_add = nodes[lson].tag_add * nodes[p].revTag + nodes[p].tag_add;
    nodes[rson].tag_add = nodes[rson].tag_add * nodes[p].revTag + nodes[p].tag_add;

    nodes[p].revTag = 1, nodes[p].tag_add = 0;
}

void pushup(int p) { nodes[p].max_val = max(nodes[lson].max_val, nodes[rson].max_val), nodes[p].min_val = min(nodes[lson].min_val, nodes[rson].min_val); }

void build(int l, int r, int p)
{
    if (l == r)
        return (void)(nodes[p].min_val = ci[l], nodes[p].max_val = ci[l], nodes[p].revTag = 1);
    build(l, mid, lson), build(mid + 1, r, rson);
    pushup(p);
}

void updateReverse(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
    {
        swap(nodes[p].max_val, nodes[p].min_val);
        nodes[p].max_val *= -1, nodes[p].min_val *= -1;
        nodes[p].revTag *= -1, nodes[p].tag_add *= -1;
        return;
    }
    pushdown(p);
    if (ql <= mid)
        updateReverse(ql, qr, l, mid, lson);
    if (mid < qr)
        updateReverse(ql, qr, mid + 1, r, rson);
    pushup(p);
}

void update(int ql, int qr, int l, int r, int p, int val)
{
    if (ql <= l && r <= qr)
    {
        nodes[p].max_val += val, nodes[p].min_val += val, nodes[p].tag_add += val;
        return;
    }
    pushdown(p);
    if (ql <= mid)
        update(ql, qr, l, mid, lson, val);
    if (mid < qr)
        update(ql, qr, mid + 1, r, rson, val);
    pushup(p);
}

pii merge(pii A, pii B) { return make_pair(min(A.first, B.first), max(A.second, B.second)); }

pii query(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
        return make_pair(nodes[p].min_val, nodes[p].max_val);
    pushdown(p);
    pii ret = make_pair(0x3f3f3f3f, -0x3f3f3f3f);
    if (ql <= mid)
        ret = merge(ret, query(ql, qr, l, mid, lson));
    if (mid < qr)
        ret = merge(ret, query(ql, qr, mid + 1, r, rson));
    return ret;
}

#undef mid

bool lft = true;

void subtask4Handler()
{
    build(1, n, 1);
    while (q--)
    {
        int x, y;
        scanf("%s", cmdlet + 1);
        if (cmdlet[1] == 'q')
        {
            scanf("%d%d", &x, &y);
            if (cmdlet[2] == 'u')
            {
                int l = 1, r = x, res = x + 1;
                while (l <= r)
                {
                    int mid = (l + r) >> 1;
                    pii tube = query(mid, x, 1, n, 1);
                    if ((lft && tube.first >= y) || (!lft && tube.second <= y))
                        r = mid - 1, res = mid;
                    else
                        l = mid + 1;
                }
                printf("%d\n", x - res + 1);
            }
            else
            {
                int l = x, r = n, res = x - 1;
                while (l <= r)
                {
                    int mid = (l + r) >> 1;
                    pii tube = query(x, mid, 1, n, 1);
                    if ((lft && tube.first >= y) || (!lft && tube.second <= y))
                        l = mid + 1, res = mid;
                    else
                        r = mid - 1;
                }
                printf("%d\n", res - x + 1);
            }
        }
        else
        {
            if ((cmdlet[1] == 'l' && lft) || (cmdlet[1] == 'r' && (!lft)))
                continue;
            lft ^= 1;
            updateReverse(1, n, 1, n, 1), update(1, n, 1, n, 1, m + 1);
        }
    }
}

} // namespace Subtask4

int main()
{

    freopen("wind.in", "r", stdin);
    freopen("wind.out", "w", stdout);
    
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ci[i]);
    scanf("%d", &q);
    if (max(n, max(m, q)) <= 100)
        return Subtask3::subtask3Handler(), 0;
    if (q == 1)
        return Subtask2::subtask2Handler(), 0;
    if (n % 10 == 9)
        return Subtask4::subtask4Handler(), 0;
    return 0;
}