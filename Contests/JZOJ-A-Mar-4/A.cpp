// A.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 1e6 + 200;
int n, m, fa[MAX_N << 2];
int find(int x) { return fa[x] == x ? fa[x] : fa[x] = find(fa[x]); }
void unite(int x, int y) { fa[find(x)] = fa[find(y)]; }
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= 2 * n; i++)
        fa[i] = i;
    while (m--)
    {
        int opt, x, y;
        scanf("%d%d%d", &opt, &x, &y);
        if (opt == 0)
            unite(x, y), unite(x + n, y + n);
        else if (opt == 1 || opt == 2)
            unite(x, y + n), unite(x + n, y);
        else if (find(x) == find(y) || find(x + n) == find(y + n))
            puts("1");
        else
            puts("0");
    }
    return 0;
}