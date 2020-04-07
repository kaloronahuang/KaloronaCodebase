// P3570.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

int n, color, seq[MAX_N], len1, len2, p1[MAX_N], p2[MAX_N], lft[MAX_N], rig[MAX_N], dp[MAX_N], last_pos[MAX_N], cnt[MAX_N];
int bucket[MAX_N][2];

int main()
{
    scanf("%d%d", &n, &color);
    for (int i = 1; i <= n; i++)
        scanf("%d", &seq[i]);
    scanf("%d%d", &len1, &len2);
    for (int i = 1; i <= len1; i++)
        scanf("%d", &p1[i]), last_pos[p1[i]] = i;
    for (int i = 1; i <= n; i++)
    {
        if (last_pos[seq[i]] != 0)
            dp[last_pos[seq[i]]] = (last_pos[seq[i]] == 1) ? i : dp[last_pos[seq[i]] - 1];
        lft[i] = dp[len1];
    }
    memset(last_pos, 0, sizeof(last_pos));
    for (int i = 1; i <= len2; i++)
        scanf("%d", &p2[i]), last_pos[p2[i]] = i, dp[i] = n + 1;
    for (int i = n; i >= 1; i--)
    {
        if (last_pos[seq[i]] != 0)
            dp[last_pos[seq[i]]] = (last_pos[seq[i]] == 1) ? i : dp[last_pos[seq[i]] - 1];
        rig[i] = dp[len2];
    }
    vector<int> ans;
    for (int i = 1; i <= n; i++)
        bucket[seq[i]][1]++;
    int acc = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int ptr = lft[i - 1]; ptr < lft[i]; ptr++)
        {
            bucket[seq[ptr]][0]++;
            if (bucket[seq[ptr]][0] == 1 && bucket[seq[ptr]][1] > 0)
                acc++;
        }
        for (int ptr = rig[i]; ptr > rig[i - 1]; ptr--)
        {
            bucket[seq[ptr]][1]--;
            if (bucket[seq[ptr]][1] == 0 && bucket[seq[ptr]][0] > 0)
                acc--;
        }
        if (seq[i] == p1[len1] && acc)
            ans.push_back(i);
    }
    printf("%lld\n", 1LL * ans.size());
    for (int x : ans)
        printf("%d ", x);
    return 0;
}