// LOJ3246.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3030, mod = 1e9 + 7;

int n, m, mem[MAX_N * MAX_N], val[MAX_N * MAX_N], aff[MAX_N][MAX_N], block;
char str[MAX_N][MAX_N];

int find(int x) { return mem[x] == x ? x : mem[x] = find(mem[x]); }

void merge(int x, int y)
{
    int fx = find(x), fy = find(y);
    if (fx == fy)
        return;
    val[fx] = 1LL * val[fx] * val[fy] % mod;
    mem[fy] = fx;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%s", str[i] + 1);
    for (int i = 1; i <= n * m; i++)
        mem[i] = i, val[i] = 1;
    for (int i = n; i >= 1; i--)
    {
        int curt = block;
        for (int j = 1; j <= m; j++)
            if (str[i][j] == '.' && str[i][j - 1] != '.')
                aff[i][j] = ++block;
            else
                aff[i][j] = block;
        for (int j = 1; j <= m; j++)
            if (str[i][j] == '.' && str[i + 1][j] == '.')
                merge(aff[i][j], aff[i + 1][j]);
        for (int j = curt + 1; j <= block; j++)
            if (find(j) == j)
                val[j] = (0LL + val[j] + 1) % mod;
    }
    int ans = 1;
    for (int i = 1; i <= block; i++)
        if (i == find(i))
            ans = 1LL * ans * val[i] % mod;
    printf("%d\n", ans);
    return 0;
}