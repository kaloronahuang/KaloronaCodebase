// CH1602.cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int maxn = 100000 * 40;
int trie[maxn][2], arr[maxn], n, current = 2;
void insert(int num)
{
    int pnode = 1;
    for (int i = 30; i >= 0; i--)
    {
        int bit = (num >> i) & 1;
        if (trie[pnode][bit] == 0)
            trie[pnode][bit] = current++;
        pnode = trie[pnode][bit];
    }
}
int getBiggest(int num)
{
    int ans = 0, pnode = 1;
    for (int i = 30; i >= 0; i--)
    {
        int bit = (num >> i) & 1;
        if (trie[pnode][bit ^ 1] != 0)
            pnode = trie[pnode][bit ^ 1], ans |= (1 << i);
        else
            pnode = trie[pnode][bit];
    }
    return ans;
}
int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]), insert(arr[i]);
    int ans = 0;
    for (int i = 0; i < n; i++)
        ans = max(ans, getBiggest(arr[i]));
    printf("%d", ans);
    return 0;
}