// E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int T, n, m, col[MAX_N];
vector<int> psrc[MAX_N];

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++)
            psrc[i].clear(), col[i] = 0;
        for (int i = 1, u, v; i <= m; i++)
            scanf("%d%d", &u, &v), psrc[v].push_back(u);
        for (int v = 1; v <= n; v++)
            for (int u : psrc[v])
            {
                if (col[u] == 1)
                    col[v] = 2;
                if (col[v] != 2 && col[u] == 0)
                    col[v] = 1;
            }
        vector<int> ansBox;
        for (int i = 1; i <= n; i++)
            if (col[i] == 2)
                ansBox.push_back(i);
        printf("%d\n", int(ansBox.size()));
        for (int x : ansBox)
            printf("%d ", x);
        puts("");
    }
    return 0;
}