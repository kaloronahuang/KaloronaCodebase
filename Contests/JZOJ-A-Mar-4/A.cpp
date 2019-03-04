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
    for (int i = 1; i <= 4 * n; i++)
        fa[i] = i;
    while (m--)
    {
        int opt, x, y;
        scanf("%d%d%d", &opt, &x, &y);
        if (opt == 0)
            unite(x, y), unite(x + n, y + n), unite(x + 2 * n, y + 2 * n), unite(x + 3 * n, y + 3 * n);
        else if (opt == 1)
            unite(x, y + n), unite(x + n, y), unite(x + 2 * n, y + 3 * n), unite(x + 3 * n, y + 2 * n);
        else if (opt == 2)
            unite(x, y + 2 * n), unite(x + n, y + 3 * n), unite(x + 2 * n, y), unite(x + 3 * n, y + n);
        else
        {
            if (find(x) == find(y) || find(x + n) == find(y + n) || find(x + 2 * n) == find(y + 2 * n) || find(x + 3 * n) == find(y + 3 * n))
                puts("1");
            else
                puts("0");
        }
    }
    return 0;
}