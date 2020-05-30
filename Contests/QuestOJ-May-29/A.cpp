// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2010, BLOCK = 40;

int n, m, q, mat[MAX_N][MAX_N], mem[MAX_N * MAX_N];
char mp[MAX_N][MAX_N];

int getId(int x, int y) { return (x - 1) * m + y; }

int find(int x) { return mem[x] == x ? x : mem[x] = find(mem[x]); }

bool in(int l, int x, int r) { return l <= x && x <= r; }

pair<int, int> getCord(int id) { return make_pair((id - 1) / m + 1, (id - 1) % m + 1); }

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%s", mp[i] + 1);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            mem[getId(i, j)] = getId(i, j);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            if (mp[i][j] == mp[i - 1][j] && find(getId(i, j)) != find(getId(i - 1, j)))
                mem[find(getId(i, j))] = find(getId(i - 1, j));
            if (mp[i][j] == mp[i][j - 1] && find(getId(i, j)) != find(getId(i, j - 1)))
                mem[find(getId(i, j))] = find(getId(i, j - 1));
        }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            mat[i][j] = find(getId(i, j)) == getId(i, j);
            mat[i][j] += mat[i][j - 1] + mat[i - 1][j] - mat[i - 1][j - 1];
        }
    scanf("%d", &q);
    while (q--)
    {
        int ret = 0, xl, yl, xr, yr;
        scanf("%d%d%d%d", &xl, &yl, &xr, &yr);
        ret += mat[xr][yr] - mat[xl - 1][yr] - mat[xr][yl - 1] + mat[xl - 1][yl - 1];
        set<int> ids;
        for (int i = xl; i <= xr; i++)
        {
            pair<int, int> crd = getCord(find(getId(i, yl)));
            if (!(in(xl, crd.first, xr) && in(yl, crd.second, yr)))
                ids.insert(find(getId(i, yl)));
            crd = getCord(find(getId(i, yr)));
            if (!(in(xl, crd.first, xr) && in(yl, crd.second, yr)))
                ids.insert(find(getId(i, yr)));
        }
        for (int i = yl + 1; i <= yr - 1; i++)
        {
            pair<int, int> crd = getCord(find(getId(xl, i)));
            if (!(in(xl, crd.first, xr) && in(yl, crd.second, yr)))
                ids.insert(find(getId(xl, i)));
            crd = getCord(find(getId(xr, i)));
            if (!(in(xl, crd.first, xr) && in(yl, crd.second, yr)))
                ids.insert(find(getId(xr, i)));
        }
        ret += ids.size();
        printf("%d\n", ret);
    }
    return 0;
}