// P1360.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, MAX_C = 30;

int n, prefix[MAX_C], ans, m;
map<vector<int>, int> mp;

int main()
{
    scanf("%d%d", &n, &m);
    vector<int> now(m);
    for (int i = 0; i < m; i++)
        now[i] = 0;
    mp[now] = 0;
    for (int i = 1, stat; i <= n; i++)
    {
        scanf("%d", &stat);
        for (int j = 0; j < m; j++)
            if (stat & (1 << j))
                prefix[j]++;
        for (int j = 0; j < m; j++)
            now[j] = prefix[j] - prefix[0];
        if (mp.count(now) != 0)
            ans = max(ans, i - mp[now]);
        else
            mp[now] = i;
    }
    printf("%d", ans);
    return 0;
}