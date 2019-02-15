// C.cpp
// Complexity: O(32n + 32m)
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 1e5 + 100;
int trie[MAX_N * 64][2], mark[MAX_N * 64], tot = 1, tmp;
void insert(int num, int mk)
{
    int p = 1;
    for (int i = 31; i >= 0; i--)
    {
        int bit = (num >> i) & 1;
        if (trie[p][bit] == 0)
            trie[p][bit] = ++tot;
        p = trie[p][bit];
    }
    mark[p] = mk;
}
int query(int num)
{
    int p = 1;
    for (int i = 31; i >= 0; i--)
    {
        int bit = (num >> i) & 1, desire = bit ^ 1;
        if (trie[p][desire] != 0)
            p = trie[p][desire];
        else
            p = trie[p][bit];
    }
    return mark[p];
}
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &tmp), insert(tmp, i);
    for (int i = 1; i <= m; i++)
        scanf("%d", &tmp), printf("%d\n", query(tmp));
    return 0;
}