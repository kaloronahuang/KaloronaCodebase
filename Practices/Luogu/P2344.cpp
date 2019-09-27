// P2344.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int mod = 1000000009, MAX_N = 2e5 + 200;

int n, tree[MAX_N];
ll prefix[MAX_N];
vector<ll> mapping;

inline int lowbit(int x) { return x & -x; }

void update(int x, int d)
{
    for (; x < MAX_N; x += lowbit(x))
        tree[x] = (1LL * d + 1LL * tree[x]) % mod;
}

int query(int x)
{
    int ans = 0;
    for (; x > 0; x -= lowbit(x))
        ans = (1LL * ans + 1LL * tree[x]) % mod;
    return ans;
}

int main()
{
    scanf("%d", &n);
    mapping.push_back(0);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &prefix[i]), prefix[i] += prefix[i - 1], mapping.push_back(prefix[i]);
    sort(mapping.begin(), mapping.end());
    mapping.erase(unique(mapping.begin(), mapping.end()), mapping.end());
    update(lower_bound(mapping.begin(), mapping.end(), 0) - mapping.begin() + 1, 1);
    ll dp = 0;
    for (int i = 1; i <= n; i++)
    {
        int id = lower_bound(mapping.begin(), mapping.end(), prefix[i]) - mapping.begin() + 1;
        dp = query(id);
        update(id, dp);
    }
    printf("%lld", dp);
    return 0;
}