// CF1242B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, m;
set<int> st;
set<int>::iterator it;
map<int, bool> mp[MAX_N];

void dfs(int u)
{
    st.erase(st.find(u));
    int last = 0;
    while (!st.empty())
    {
        it = st.upper_bound(last);
        if (it == st.end())
            break;
        last = *it;
        if (mp[u].count(last) == 0)
            dfs(last);
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v), mp[u][v] = mp[v][u] = true;
    for (int i = 1; i <= n; i++)
        st.insert(i);
    int block_num = 0;
    for (int i = 1; i <= n; i++)
        if (st.find(i) != st.end())
            block_num++, dfs(i);
    printf("%d", block_num - 1);
    return 0;
}