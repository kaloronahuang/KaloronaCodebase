// BZ4066.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 200100, threshold = 10000;

typedef long long ll;

int n, current_round, ptot;
ll last_ans;

// KD-Tree starts here;

struct node
{
    int xi[2], max_val[2], min_val[2], lson, rson, val;
    ll sum;
    int &operator[](const int &idx) { return xi[idx]; }
    bool operator<(const node &rhs) const { return xi[current_round] < rhs.xi[current_round]; }
} nodes[MAX_N], pending, tmp[MAX_N];

void pushup(int p)
{
    for (int i = 0; i < 2; i++)
    {
        nodes[p].max_val[i] = nodes[p].min_val[i] = nodes[p][i];
        if (nodes[p].lson)
            nodes[p].max_val[i] = max(nodes[p].max_val[i], nodes[nodes[p].lson].max_val[i]);
        if (nodes[p].rson)
            nodes[p].max_val[i] = max(nodes[p].max_val[i], nodes[nodes[p].rson].max_val[i]);
        if (nodes[p].lson)
            nodes[p].min_val[i] = min(nodes[p].min_val[i], nodes[nodes[p].lson].min_val[i]);
        if (nodes[p].rson)
            nodes[p].min_val[i] = min(nodes[p].min_val[i], nodes[nodes[p].rson].min_val[i]);
    }
    nodes[p].sum = nodes[p].val + nodes[nodes[p].lson].sum + nodes[nodes[p].rson].sum;
}

int build(int l, int r)
{
    if (l > r)
        return 0;
    int mid = (l + r) >> 1;
    nth_element(tmp + l, tmp + mid, tmp + r + 1);
    nodes[mid] = tmp[mid], current_round ^= 1;
    nodes[mid].lson = build(l, mid - 1), nodes[mid].rson = build(mid + 1, r);
    current_round ^= 1, pushup(mid);
    return mid;
}

int insert(int p)
{
    if (p == 0)
    {
        nodes[p = ++ptot] = pending, pushup(p);
        return p;
    }
    if (nodes[p][0] == pending[0] && nodes[p][1] == pending[1])
        return (nodes[p].val += pending.val, nodes[p].sum += pending.val, p);
    if (pending[current_round] < nodes[p][current_round])
        current_round ^= 1, nodes[p].lson = insert(nodes[p].lson), current_round ^= 1;
    else
        current_round ^= 1, nodes[p].rson = insert(nodes[p].rson), current_round ^= 1;
    pushup(p);
    return p;
}

ll query(int p, int x1, int y1, int x2, int y2)
{
    if (p == 0)
        return 0;
    if (x1 <= nodes[p].min_val[0] && nodes[p].max_val[0] <= x2 && y1 <= nodes[p].min_val[1] && nodes[p].max_val[1] <= y2)
        return nodes[p].sum;
    if (x2 < nodes[p].min_val[0] || x1 > nodes[p].max_val[0] || y2 < nodes[p].min_val[1] || y1 > nodes[p].max_val[1])
        return 0;
    ll ret = 0;
    if (x1 <= nodes[p][0] && nodes[p][0] <= x2 && y1 <= nodes[p][1] && nodes[p][1] <= y2)
        ret += nodes[p].val;
    ret += query(nodes[p].lson, x1, y1, x2, y2) + query(nodes[p].rson, x1, y1, x2, y2);
    return ret;
}

int main()
{
    ll opt, x1, y1, x2, y2, val, root;
    scanf("%d", &n);
    while (~scanf("%lld", &opt))
    {
        if (opt == 3)
            break;
        if (opt == 1)
        {
            scanf("%lld%lld%lld", &x1, &x2, &val);
            pending[0] = x1 ^ last_ans, pending[1] = x2 ^ last_ans, pending.val = val ^ last_ans;
            root = insert(root);
            if (ptot % threshold == 0)
            {
                for (int i = 1; i <= ptot; i++)
                    tmp[i] = nodes[i];
                root = build(1, ptot);
            }
        }
        else
        {
            scanf("%lld%lld%lld%lld", &x1, &y1, &x2, &y2);
            x1 ^= last_ans, y1 ^= last_ans, x2 ^= last_ans, y2 ^= last_ans;
            printf("%lld\n", last_ans = query(root, x1, y1, x2, y2));
        }
    }
    return 0;
}