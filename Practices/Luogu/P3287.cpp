// P3287.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 10010, MAX_DOM = 5050;

int n, seq[MAX_N], k, upper, tree[MAX_DOM + 550][555];

inline int lowbit(int x) { return x & -x; }

inline void update(int x, int y, int d)
{
    for (; x <= upper; x += lowbit(x))
        for (int i = y; i <= k + 1; i += lowbit(i))
            tree[x][i] = max(tree[x][i], d);
}

inline int query(int x, int y)
{
    int ans = 0;
    for (; x; x -= lowbit(x))
        for (int i = y; i; i -= lowbit(i))
            ans = max(tree[x][i], ans);
    return ans;
}

int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d", &seq[i]), upper = max(upper, seq[i] + k);
    int ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = k; j >= 0; j--)
        {
            int tmp = query(seq[i] + j, j + 1) + 1;
            ans = max(ans, tmp);
            update(seq[i] + j, j + 1, tmp);
        }
    printf("%d", ans);
    return 0;
}