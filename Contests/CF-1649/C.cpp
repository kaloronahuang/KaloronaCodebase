// C.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int n, m;
map<int, vector<int>> mp[2];

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1, c; j <= m; j++)
            scanf("%d", &c), mp[0][c].push_back(i), mp[1][c].push_back(j);
    ll gans = 0;
    for (int c = 0; c < 2; c++)
        for (auto &u : mp[c])
        {
            vector<int> uarr = u.second;
            sort(uarr.begin(), uarr.end());
            int siz = uarr.size();
            for (int i = 0; i < siz; i++)
                gans += 1LL * i * uarr[i] - 1LL * (siz - i - 1) * uarr[i];
        }
    printf("%lld\n", gans);
    return 0;
}