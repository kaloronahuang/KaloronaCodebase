// C.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 3e5 * 20 + 20000;
int trie[MAX_N][2], tot = 1, sum[MAX_N], n, even[MAX_N], odd[MAX_N];
void insert(int num, int id)
{
    int p = 1;
    for (int i = 30; i >= 0; i--)
    {
        int bit = (num >> i) & 1;
        if (trie[p][bit] == 0)
            trie[p][bit] = ++tot;
        p = trie[p][bit];
    }
    if (id & 1)
        odd[p]++;
    else
        even[p]++;
}
int find(int num)
{
    int p = 1;
    for (int i = 30; i >= 0; i--)
    {
        int bit = (num >> i) & 1;
        if (trie[p][bit] == 0)
            return -1;
        p = trie[p][bit];
    }
    return p;
}
int main()
{
    scanf("%d", &n);
    long long ans = 0;
    insert(0, 0);
    for (int r = 1; r <= n; r++)
    {
        scanf("%d", &sum[r]), sum[r] ^= sum[r - 1];
        int id = find(sum[r]);
        if (id != -1)
            if (r & 1)
                ans += odd[id];
            else
                ans += even[id];
        insert(sum[r], r);
    }
    printf("%lld", ans);
    return 0;
}