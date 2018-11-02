// P3374.cpp
#include <iostream>
#include <vector>

using namespace std;

const int maxn = 5000000;

int arr[maxn];
int tree[2 * maxn];
int n;
int tree_n;

void init(int n)
{
    n = n + 1;
    tree_n = 2 * n;
    for (int i = 0; i < n; i++)
        arr[i] = 0;
    for (int i = 0; i < tree_n; i++)
        tree[i] = 0;
}

inline int lowbit(int idx)
{
    return idx & -idx;
}

void Add(int x, int d)
{
    int siz = tree_n;
    while (x < siz)
        tree[x] += d, x += lowbit(x);
}

int Query(int x)
{
    int ret = 0;
    while (x > 0)
        ret += tree[x], x -= lowbit(x);
    return ret;
}

int main()
{
    int n, m, num;
    cin >> n >> m;
    init(n);
    int last = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> num, Add(i, num - last);
        last = num;
    }
    for (int i = 0; i < m; i++)
    {
        int opt, x, y, k;
        cin >> opt >> x;
        if (opt == 1)
        {
            cin >> y >> k;
            Add(x, k);
            Add(y + 1, -k);
        }
        else
            cout << Query(x) << endl;
    }
    return 0;
}