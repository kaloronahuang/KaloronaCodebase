// CF1086A.cpp
#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

pii pts[3];
map<pii, bool> mp;

int func(int x) { return x >= 0 ? 1 : -1; }

int main()
{
    for (int i = 0; i < 3; i++)
        scanf("%d%d", &pts[i].first, &pts[i].second);
    sort(pts, pts + 3);
    vector<pii> ansBox;
    for (int i = pts[0].first, j = pts[0].second, rd = 0; i <= pts[2].first; i++)
    {
        if (!mp.count(make_pair(i, j)))
            ansBox.push_back(make_pair(i, j)), mp[make_pair(i, j)] = true;
        if (rd == 0 && i == pts[rd + 1].first)
        {
            for (; j != pts[rd + 1].second; j += func(pts[rd + 1].second - j))
            {
                if (!mp.count(make_pair(i, j)))
                    ansBox.push_back(make_pair(i, j)), mp[make_pair(i, j)] = true;
            }
            if (!mp.count(make_pair(i, j)))
                ansBox.push_back(make_pair(i, j)), mp[make_pair(i, j)] = true;
            rd++;
            for (; j != pts[rd + 1].second; j += func(pts[rd + 1].second - j))
            {
                if (!mp.count(make_pair(i, j)))
                    ansBox.push_back(make_pair(i, j)), mp[make_pair(i, j)] = true;
            }
            if (!mp.count(make_pair(i, j)))
                ansBox.push_back(make_pair(i, j)), mp[make_pair(i, j)] = true;
        }
    }
    printf("%d\n", int(ansBox.size()));
    for (auto &x : ansBox)
        printf("%d %d\n", x.first, x.second);
    return 0;
}