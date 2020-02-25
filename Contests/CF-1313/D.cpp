// D.cpp
#pragma GCC optimize(2)
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int n, m, limit, dp[MAX_N][(1 << 8)];
vector<int> vec;
pair<int, int> segs[MAX_N];
map<int, int> overlay[MAX_N];
vector<int> segover[MAX_N];
set<pair<int, int> /**/> st;

int ripe(int x) { return lower_bound(vec.begin(), vec.end(), x) - vec.begin() + 1; }

int getlen(int x) { return segs[x].second - segs[x].first; }

int main()
{
    scanf("%d%d%d", &n, &m, &limit);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", &segs[i].first, &segs[i].second);
        vec.push_back(segs[i].first);
        vec.push_back(segs[i].second + 1);
        st.insert(segs[i]);
    }
    sort(vec.begin(), vec.end()), vec.erase(unique(vec.begin(), vec.end()), vec.end());
    int seg_siz = vec.size();
    set<pair<int, int> /**/>::iterator it = st.begin();
    n = st.size();
    for (int i = 1; i <= n; i++)
        segs[i] = *it, it++;
    for (int i = 1; i <= n; i++)
    {
        int l = ripe(segs[i].first), r = ripe(segs[i].second + 1);
        overlay[l][i] = 1;
        overlay[r][i] = -1;
    }
    for (int i = 1; i <= seg_siz; i++)
    {
        segover[i] = segover[i - 1];
        for (auto pr : overlay[i])
            if (pr.second == -1)
            {
                for (vector<int>::iterator it = segover[i].begin(); it != segover[i].end(); it++)
                    if (*it == pr.first)
                    {
                        segover[i].erase(it);
                        break;
                    }
            }
            else
                segover[i].push_back(pr.first);
    }
    int ans = 0;
    for (int i = 1; i < seg_siz; i++)
    {
        map<int, int> idx;
        for (int j = 0, siz = segover[i].size(); j < siz; j++)
            idx[segover[i][j]] = j;
        // enumerating the previous stat;
        int pre_siz = segover[i - 1].size();
        for (int pre_stat = 0; pre_stat < (1 << pre_siz); pre_stat++)
        {
            int current_stat = (1 << segover[i].size()) - 1;
            int compulsory = 0;
            for (int j = 0; j < pre_siz; j++)
                if (((~pre_stat) & (1 << j)) && idx.count(segover[i - 1][j]))
                    current_stat ^= (1 << idx[segover[i - 1][j]]);
                else if ((pre_stat & (1 << j) && idx.count(segover[i - 1][j])))
                    compulsory ^= (1 << idx[segover[i - 1][j]]);
            for (int stat = current_stat;; stat = (stat - 1) & current_stat)
                if ((stat & compulsory) == compulsory)
                {
                    int const_term = vec[i] - vec[i - 1];
                    dp[i][stat] = max(dp[i - 1][pre_stat] + const_term * (__builtin_popcount(stat) & 1), dp[i][stat]);
                    if (i == seg_siz - 1)
                        ans = max(ans, dp[i][stat]);
                    if (stat == 0)
                        break;
                }
                else if (stat == 0)
                    break;
        }
    }
    printf("%d\n", ans);
    return 0;
}