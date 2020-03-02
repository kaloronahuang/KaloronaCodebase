// war.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1.5e5 + 200;

int n, m, p, ai[MAX_N];

int main()
{
    freopen("war.in", "r", stdin);
    freopen("war.out", "w", stdout);
    scanf("%d%d%d", &n, &m, &p);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    while (m--)
    {
        int opt, l, r, id;
        scanf("%d%d%d", &opt, &l, &r);
        if (opt == 1)
        {
            scanf("%d", &id);
            for (int i = l; i <= r; i++)
                ai[i] = id;
        }
        else if (opt == 2)
            for (int i = l; i <= r; i++)
                ai[i]++;
        else
        {
            map<int, int> mp;
            int req = ceil(double(r - l + 1) * p / 100.0);
            for (int i = l; i <= r; i++)
                mp[ai[i]]++;
            vector<int> ansBox;
            for (map<int, int>::iterator it = mp.begin(); it != mp.end(); it++)
                if (it->second >= req)
                    ansBox.push_back(it->first);
            printf("%d ", int(ansBox.size()));
            for (int i = 0, siz = ansBox.size(); i < siz; i++)
                printf("%d ", ansBox[i]);
            puts("");
        }
    }
    return 0;
}