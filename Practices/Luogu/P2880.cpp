// P2880.cpp
#include <iostream>

using namespace std;

const int maxn = 500020;
const int INF = 0x7fffffff;
int treeMAX[2 * maxn];
int treeMIN[2 * maxn];
int n, q;
int arr[maxn];

inline int lowbit(int x)
{
    return x & (-x);
}

int query(int l, int r)
{
    int max_v = -1;
    int min_v = INF;
    while (r >= l)
    {
        while (r - lowbit(r) >= l)
        {
            max_v = max(max_v, treeMAX[r]), min_v = min(min_v, treeMIN[r]);
            r -= lowbit(r);
        }
        max_v = max(arr[r], max_v), min_v = min(arr[r], min_v);
        r--;
    }
    return max_v - min_v;
}

void change(int x, int d)
{
    while (x <= n)
    {
        treeMAX[x] = max(treeMAX[x], d);
        treeMIN[x] = min(treeMIN[x], d);
        x += lowbit(x);
    }
}

int main()
{
    cin >> n >> q;
    fill(treeMAX, treeMAX + 2 * n + 10, -1);
    fill(treeMIN, treeMIN + 2 * n + 10, 1e9);
    for (int i = 1; i <= n; i++)
        cin >> arr[i], change(i, arr[i]);
    int l, r;
    for (int i = 0; i < q; i++)
        cin >> l >> r, cout << query(l, r) << endl;
    return 0;
}