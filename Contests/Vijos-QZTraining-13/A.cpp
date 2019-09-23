// A.cpp
#include <bits/stdc++.h>
#define pr pair<int, int>

using namespace std;

const int MAX_N = 3e5 + 200;

int prefix_l[MAX_N], prefix_r[MAX_N], seq[MAX_N], n;
int pos_l[MAX_N], pos_r[MAX_N];
vector<pr> ans;

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &seq[i]);
        prefix_l[i] += prefix_l[i - 1], prefix_r[i] += prefix_r[i - 1];
        if (seq[i] == 1)
            prefix_l[i]++, pos_l[prefix_l[i]] = i;
        else
            prefix_r[i]++, pos_r[prefix_r[i]] = i;
    }
    for (int t = 1; t <= n; t++)
    {
        int pos = 0, lft_rnd = 0, rig_rnd = 0, turn;
        while (true)
        {
            if (pos == n)
            {
                // even;
                if (lft_rnd == rig_rnd)
                    break;
                // result comes conflicting with the real one;
                if ((lft_rnd > rig_rnd && turn == 2) || (lft_rnd < rig_rnd && turn == 1))
                    break;
                ans.push_back(make_pair(max(lft_rnd, rig_rnd), t));
                break;
            }
            int g1 = prefix_l[pos] + t, g2 = prefix_r[pos] + t;
            if (pos_l[g1] == 0 && pos_r[g2] == 0)
                break;
            if (pos_l[g1] == 0 || (pos_r[g2] != 0 && pos_r[g2] < pos_l[g1]))
                rig_rnd++, turn = 2, pos = pos_r[g2];
            else
                lft_rnd++, turn = 1, pos = pos_l[g1];
        }
    }
    sort(ans.begin(), ans.end());
    printf("%lld\n", ans.size());
    for (int i = 0, siz = ans.size(); i < siz; i++)
        printf("%d %d\n", ans[i].first, ans[i].second);
    return 0;
}