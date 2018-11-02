// P3372.cpp
// Segment tree;
#include <iostream>
using namespace std;

const int maxn = 100010;
int arr[maxn];

struct segTree
{
    int tree[4 * maxn];

    void build(int st, int ed, int nodeIndex)
    {
        if (st == ed)
            tree[nodeIndex] = arr[st];
        else
        {
            int m = (st + ed) / 2;
            build(st, m, 2 * nodeIndex), build(m + 1, ed, 2 * nodeIndex + 1);
            // 2 trees update.
            tree[nodeIndex] = tree[2 * nodeIndex] + tree[2 * nodeIndex + 1];
        }
    }

    int query(int l, int r, int curl, int curr, int intervalIdx)
    {
        if (l <= curl && r >= curr || l == r)
            return tree[intervalIdx];
        int mid = (curl + curr) / 2;
        int sum = 0;
        if (l <= mid)
            sum += query(l, r, curl, mid, 2 * n);
        if (r > mid)
            sum += query(l, r, mid + 1, curr, intervalIdx * 2 + 1);
        return sum;
    }
};

int main()
{
}