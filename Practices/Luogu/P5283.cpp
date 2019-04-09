// P5283.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAX_N = 5e5 * 35;
struct npair
{
    int point, rk;
    ll val;
    bool operator<(const npair &np) const { return val < np.val; }
};
int trie[MAX_N][2], size[MAX_N], treetot = 1, current_rank;
ll n, k, arr[MAX_N];
priority_queue<npair> pq;
void insert(ll num)
{
    int p = 1;
    for (int i = 31; i >= 0; i--)
    {
        int bit = (num >> i) & 1;
        size[p]++;
        if (trie[p][bit] == 0)
            trie[p][bit] = ++treetot;
        p = trie[p][bit];
    }
    size[p]++;
}
ll atRank(ll num, int rk)
{
    int p = 1;
    ll ans = 0;
    for (int i = 31; i >= 0; i--)
    {
        int bit = ((num >> i) & 1);
        if (trie[p][bit ^ 1] == 0)
            p = trie[p][bit];
        else if (rk <= size[trie[p][bit ^ 1]])
            p = trie[p][bit ^ 1], ans |= 1LL << i;
        else
            rk -= size[trie[p][bit ^ 1]], p = trie[p][bit];
    }
    return ans;
}
int main()
{
    scanf("%lld%lld", &n, &k), k *= 2;
    for (int i = 1; i <= n; i++)
        scanf("%lld", &arr[i]), arr[i] = arr[i - 1] ^ arr[i];
    for (int i = 0; i <= n; i++)
        insert(arr[i]);
    for (int i = 0; i <= n; i++)
        pq.push(npair{i, 1, atRank(arr[i], 1)});
    ll ans = 1;
    for (int i = 1; i <= k; i++)
    {
        npair np = pq.top();
        ans += np.val, pq.pop();
        if (np.rk < n)
            np.rk++, np.val = atRank(arr[np.point], np.rk), pq.push(np);
    }
    printf("%lld", ans >> 1);
    return 0;
}