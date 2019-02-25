// C.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 200200, INF = 0x3f3f3f3f;
int n, m, pos[MAX_N];
set<int> parks;
map<int, int> mp;
int main()
{
    scanf("%d%d", &n, &m);
    while (m--)
    {
        int F, x;
        scanf("%d%d", &F, &x);
        if (F == 1)
        {
            memset(pos, 0x3f, sizeof(pos));
            queue<int> q;
            for (set<int>::iterator it = parks.begin(); it != parks.end(); it++)
                q.push(*it), pos[*it] = 0;
            while (!q.empty())
            {
                int ps = q.front();
                q.pop();
                if (ps + 1 <= n && pos[ps + 1] == INF)
                    pos[ps + 1] = pos[ps] + 1, q.push(ps + 1);
                if (ps - 1 >= 1 && pos[ps - 1] == INF)
                    pos[ps - 1] = pos[ps] + 1, q.push(ps - 1);
            }
            int key = 0;
            pos[key] = 0;
            for (int i = 1; i <= n; i++)
                if (pos[i] > pos[key])
                    key = i;
            printf("%d\n", key);
            mp[x] = key, parks.insert(key);
        }
        else
            parks.erase(parks.lower_bound(mp[x]));
    }
    return 0;
}