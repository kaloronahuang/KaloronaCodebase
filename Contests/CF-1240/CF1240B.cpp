// CF1240B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e5 + 200, INF = 0x3f3f3f3f;

int q, n, seq[MAX_N], li[MAX_N], ri[MAX_N], dp[MAX_N];
vector<int> mapping;

int main()
{
    scanf("%d", &q);
    while (q--)
    {
        scanf("%d", &n), mapping.clear();
        for (int i = 1; i <= n; i++)
            scanf("%d", &seq[i]), li[i] = INF, ri[i] = -INF;
        for (int i = 1; i <= n; i++)
            li[seq[i]] = min(li[seq[i]], i), ri[seq[i]] = max(ri[seq[i]], i),
            mapping.push_back(seq[i]);
        sort(mapping.begin(), mapping.end()), mapping.erase(unique(mapping.begin(), mapping.end()), mapping.end());
        int ans = INF;
        for (int i = mapping.size() - 1, siz = i + 1; i >= 0; i--)
        {
            if (i < siz - 1 && ri[mapping[i]] < li[mapping[i + 1]])
                dp[i] = dp[i + 1] + 1;
            else
                dp[i] = 1;
            ans = min(ans, siz - dp[i]);
        }
        printf("%d\n", ans);
    }
    return 0;
}