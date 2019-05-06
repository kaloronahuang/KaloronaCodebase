// CF1093E.cpp
#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/rope>
using namespace std;
using namespace __gnu_cxx;
using namespace __gnu_pbds;

const int MAX_N = 2e5 + 2000;

template <class T>
using Tree = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

inline int lowbit(int x) { return x & (-x); }

template <int size>
struct rbtree
{
    Tree<int> trees[size + 1];

    void update(int pos, int tag, int op)
    {
        while (pos <= size)
        {
            if (op)
                trees[pos].insert(tag);
            else
                trees[pos].erase(tag);
            pos += lowbit(pos);
        }
    }

    int query(int pos, int tag)
    {
        int ans = 0;
        while (pos)
        {
            ans += trees[pos].order_of_key(tag + 1);
            pos -= lowbit(pos);
        }
        return ans;
    }

    int query(int l1, int r1, int l2, int r2)
    {
        return query(r1, r2) - query(r1, l2) - query(l1, r2) + query(l1, l2);
    }
};
rbtree<MAX_N> rbt;

int n, m, a[MAX_N], b[MAX_N], p[MAX_N];

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]), p[a[i]] = i;
    for (int i = 1; i <= n; i++)
        scanf("%d", &b[i]), b[i] = p[b[i]], rbt.update(i, b[i], 1);
    while (m--)
    {
        int la, ra, lb, rb, x, y, opt;
        scanf("%d", &opt);
        if (opt == 1)
            scanf("%d%d%d%d", &la, &ra, &lb, &rb), printf("%d\n", rbt.query(lb - 1, rb, la - 1, ra));
        else
        {
            scanf("%d%d", &x, &y);
            rbt.update(x, b[x], 0), rbt.update(y, b[y], 0);
            swap(b[x], b[y]);
            rbt.update(x, b[x], 1), rbt.update(y, b[y], 1);
        }
    }
    return 0;
}