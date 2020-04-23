// CF1329A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

typedef long long ll;

int n, m, ans[MAX_N];
pair<int, int> pts[MAX_N];

int main()
{
    scanf("%d%d", &n, &m);
    ll tot_len = 0;
    for (int i = 1; i <= m; i++)
        scanf("%d", &pts[i].first), pts[i].second = i, tot_len += pts[i].first;
    // sort(pts + 1, pts + 1 + m), reverse(pts + 1, pts + 1 + m);
    int lft_bound = 1, rig_bound = pts[1].first;
    ans[pts[1].second] = 1;
    for (int i = 2; i <= m; i++)
    {
        ll diff = tot_len - n, exp_diff = rig_bound + pts[i].first - max(rig_bound, lft_bound + pts[i].first);
        if (exp_diff <= diff)
            rig_bound = max(rig_bound, lft_bound + pts[i].first), lft_bound++, tot_len -= exp_diff, ans[pts[i].second] = lft_bound;
        else
        {
            ll exp_rig = max(rig_bound, lft_bound + pts[i].first), stage = exp_diff - diff;
            ans[pts[i].second] = exp_rig + stage - pts[i].first + 1;
            rig_bound = exp_rig + stage;
            for (int j = i + 1; j <= m; j++)
                ans[pts[j].second] = rig_bound + 1, rig_bound += pts[j].first;
            break;
        }
    }
    for (int i = 1; i <= n; i++)
        if (ans[i] + pts[i].first - 1 > n)
            puts("-1"), exit(0);
    if (tot_len < n || ans[n] + pts[n].first - 1 > n)
        puts("-1"), exit(0);
    for (int i = 1; i <= m; i++)
        printf("%d ", ans[i]);
    return 0;
}