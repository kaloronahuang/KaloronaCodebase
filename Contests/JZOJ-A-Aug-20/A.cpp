// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 201000;

int n, X, seq[MAX_N], tmp[MAX_N << 1];
vector<int> vec;

struct FenwickTree
{
    int tree[MAX_N << 1];

    inline int lowbit(int x) { return x & (-x); }

    void update(int x, int d)
    {
        for (; x <= tmp[0]; x += lowbit(x))
            tree[x] = max(tree[x], d);
    }

    int query(int x)
    {
        int ans = 0;
        for (; x; x -= lowbit(x))
            ans = max(ans, tree[x]);
        return ans;
    }
} trees[2];

int main()
{
	freopen("glo.in", "r", stdin);
	freopen("glo.out", "w", stdout);
	
    scanf("%d%d", &n, &X);
    for (int i = 1; i <= n; i++)
        scanf("%d", &seq[i]), tmp[++tmp[0]] = seq[i], tmp[++tmp[0]] = seq[i] + X;
    sort(&tmp[1], &tmp[tmp[0]] + 1);
    tmp[0] = unique(&tmp[1], &tmp[tmp[0]] + 1) - tmp - 1;
    for (int i = 1; i <= n; i++)
    {
        const int pos1 = lower_bound(&tmp[1], &tmp[tmp[0]] + 1, seq[i] + X) - tmp;
        trees[1].update(pos1, trees[0].query(pos1 - 1) + 1);
        trees[1].update(pos1, trees[1].query(pos1 - 1) + 1);
        const int cpos = lower_bound(&tmp[1], &tmp[tmp[0]] + 1, seq[i]) - tmp;
        trees[0].update(cpos, trees[0].query(cpos - 1) + 1);
    }
    printf("%d", trees[1].query(tmp[0]));
    return 0;
}
