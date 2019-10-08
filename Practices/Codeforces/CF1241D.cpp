// CF1241D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e5 + 200, INF = 0x3f3f3f3f;

int T, n, seq[MAX_N], min_bound[MAX_N], max_bound[MAX_N], dp[MAX_N], utot;
vector<int> mapping;

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n), mapping.clear();
        for (int i = 0; i < n; i++)
            min_bound[i] = INF, max_bound[i] = -INF, dp[i] = 0;
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &seq[i]), seq[i]--;
            min_bound[seq[i]] = min(min_bound[seq[i]], i);
            max_bound[seq[i]] = max(max_bound[seq[i]], i);
            mapping.push_back(seq[i]);
        }
        sort(mapping.begin(), mapping.end());
        mapping.erase(unique(mapping.begin(), mapping.end()), mapping.end());
        utot = mapping.size();
        int ans = n;
        for (int i = utot - 1; i >= 0; i--)
        {
            if (i + 1 == utot || max_bound[mapping[i]] >= min_bound[mapping[i + 1]])
                dp[i] = 1;
            else
                dp[i] = dp[i + 1] + 1;
            ans = min(ans, utot - dp[i]);
        }
        printf("%d\n", ans);
    }
    return 0;
}