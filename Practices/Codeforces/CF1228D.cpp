// CF1228D.cpp
#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1e5 + 200;

int n, m;
set<int> G[MAX_N];
bool vis[MAX_N];

int main()
{
    cin >> n >> m;
    for (int i = 1, u, v; i <= m; i++)
        cin >> u >> v, G[u].insert(v), G[v].insert(u), vis[u] = vis[v] = true;
    bool flag = true;
    for (int i = 1; i <= n; i++)
        if (!vis[i])
        {
            flag = false;
            break;
        }

    set<set<int>> st;
    for (int i = 1; i <= n; i++)
    {
        st.insert(G[i]);
        if (st.size() > 3)
        {
            flag = false;
            break;
        }
    }

    if (st.size() == 3 && flag)
        for (int i = 1; i <= n; i++)
        {
            int id = 0;
            set<set<int>>::iterator it;
            for (it = st.begin(); it != st.end(); it++)
            {
                id++;
                if (*it == G[i])
                    cout << id << " ";
            }
        }
    else
        puts("-1");

    return 0;
}