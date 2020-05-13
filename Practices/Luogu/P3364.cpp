// P3364.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 4e5 + 200;

struct info
{
    int level, strength, intelligence, attack, id;
    bool operator<(const info &rhs) const { return level < rhs.level; }
} infos[MAX_N];

int n, dp[MAX_N], nodes[MAX_N];
vector<int> mp;

int ripe(int x) { return lower_bound(mp.begin(), mp.end(), x) - mp.begin() + 1; }

int lowbit(int x) { return x & (-x); }

void update(int x, int d)
{
    for (; x < MAX_N; x += lowbit(x))
        nodes[x] = max(nodes[x], d);
}

int query(int x, int ret = 0)
{
    for (; x; x -= lowbit(x))
        ret = max(ret, nodes[x]);
    return ret;
}

void clear(int x)
{
    for (; x < MAX_N; x += lowbit(x))
        nodes[x] = 0;
}

void solve(int l, int r)
{
    if (l == r)
        return (void)(dp[infos[l].id] = max(dp[infos[l].id], 1));
    int mid = (l + r) >> 1;
    solve(l, mid);
    sort(infos + l, infos + 1 + mid, [](const info &rhs1, const info &rhs2) { return rhs1.attack < rhs2.attack; });
    sort(infos + mid + 1, infos + 1 + r, [](const info &rhs1, const info &rhs2) { return rhs1.strength < rhs2.strength; });
    for (int i = mid + 1, ptr = l; i <= r; i++)
    {
        while (ptr <= mid && infos[ptr].attack <= infos[i].strength)
            update(infos[ptr].intelligence, dp[infos[ptr].id]), ptr++;
        dp[infos[i].id] = max(dp[infos[i].id], query(infos[i].attack) + 1);
    }
    for (int i = l; i <= mid; i++)
        clear(infos[i].intelligence);
    sort(infos + mid + 1, infos + 1 + r);
    solve(mid + 1, r);
    return;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d%d%d", &infos[i].level, &infos[i].strength, &infos[i].intelligence, &infos[i].attack);
        mp.push_back(infos[i].strength), mp.push_back(infos[i].intelligence);
        mp.push_back(infos[i].attack), infos[i].id = i;
    }
    sort(infos + 1, infos + 1 + n);
    auto process = [](vector<int> &rhs) { sort(rhs.begin(), rhs.end()), rhs.erase(unique(rhs.begin(), rhs.end()), rhs.end()); };
    process(mp);
    for (int i = 1; i <= n; i++)
        infos[i].strength = ripe(infos[i].strength), infos[i].intelligence = ripe(infos[i].intelligence), infos[i].attack = ripe(infos[i].attack);
    solve(1, n), printf("%d\n", *max_element(dp + 1, dp + 1 + n));
    return 0;
}