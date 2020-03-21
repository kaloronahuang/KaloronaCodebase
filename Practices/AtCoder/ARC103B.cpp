// ARC103B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, ai[MAX_N], cost[MAX_N][2];
vector<int> pos[MAX_N];
multiset<int> ms[2];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]), pos[ai[i]].push_back(i);
    for (int i = 1; i <= 1e5; i++)
        for (auto &x : pos[i])
            cost[i][x & 1]++;
    ms[0].insert(0), ms[1].insert(0);
    for (int i = 1; i <= 1e5; i++)
        ms[0].insert(cost[i][0]), ms[1].insert(cost[i][1]);
    int ans = 0;
    for (int i = 1; i <= 1e5; i++)
    {
        // as the odd one;
        ms[0].erase(ms[0].find(cost[i][0])), ms[1].erase(ms[1].find(cost[i][1]));
        ans = max(ans, cost[i][0] + *ms[1].rbegin());
        ans = max(ans, cost[i][1] + *ms[0].rbegin());
        ms[0].insert(cost[i][0]), ms[1].insert(cost[i][1]);
    }
    printf("%d\n", n - ans);
    return 0;
}