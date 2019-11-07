// P1868.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 301010;

int nodes[MAX_N], dp[MAX_N], n;
pair<int, int> prs[MAX_N];
vector<int> mp;

inline int lowbit(int x) { return x & (-x); }

void update(int x, int d)
{
    for (; x < MAX_N; x += lowbit(x))
        nodes[x] = max(nodes[x], d);
}

int query(int x, int ans = 0)
{
    for (; x; x -= lowbit(x))
        ans = max(ans, nodes[x]);
    return ans;
}

int getId(int raw) { return lower_bound(mp.begin(), mp.end(), raw) - mp.begin() + 1; }

bool compare(pair<int, int> &a, pair<int, int> &b) { return a.second < b.second || (a.second == b.second && a.first > b.first); }

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", &prs[i].first, &prs[i].second);
        mp.push_back(prs[i].first), mp.push_back(prs[i].second);
    }
    sort(mp.begin(), mp.end()), mp.erase(unique(mp.begin(), mp.end()), mp.end());
    for (int i = 1; i <= n; i++)
        prs[i].first = getId(prs[i].first), prs[i].second = getId(prs[i].second);
    sort(prs + 1, prs + 1 + n, compare);
    for (int i = 1; i <= n; i++)
    {
        dp[prs[i].second] = max(dp[prs[i].second], dp[i - 1]);
        //printf("%d\n", query(prs[i].first - 1));
        dp[prs[i].second] = max(dp[prs[i].second], query(prs[i].first - 1) + mp[prs[i].second - 1] - mp[prs[i].first - 1] + 1);
        update(prs[i].second, dp[prs[i].second]);
    }
    int ans = 0;
    for (int i = 1, siz = mp.size(); i <= siz; i++)
        ans = max(ans, dp[i]);
    printf("%d", ans);
    return 0;
}