// ARC097B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int n, m, ai[MAX_N], mem[MAX_N];

int find(int x) { return x == mem[x] ? x : mem[x] = find(mem[x]); }

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= (n << 1); i++)
        mem[i] = i;
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]), mem[find(ai[i])] = find(i + n);
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v), mem[find(u)] = find(v);
    int ans = 0;
    for (int i = 1; i <= n; i++)
        if (find(i) == find(n + i))
            ans++;
    printf("%d\n", ans);
    return 0;
}