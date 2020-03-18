// spanning.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 22;

int n, m, mem[MAX_N], ui[MAX_N], vi[MAX_N], ans[MAX_N];

int find(int x) { return mem[x] == x ? x : mem[x] = find(mem[x]); }

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
        scanf("%d%d", &ui[i], &vi[i]);
    for (int stat = 0; stat < (1 << m); stat++)
    {
        for (int i = 1; i <= n; i++)
            mem[i] = i;
        for (int i = 0; i < m; i++)
            if ((stat & (1 << i)) && (find(ui[i + 1]) != find(vi[i + 1])))
                mem[find(ui[i + 1])] = find(vi[i + 1]);
        int cnt = 0;
        for (int i = 1; i <= n; i++)
            if (find(i) == i)
                cnt++;
        ans[cnt]++;
    }
    for (int i = 1; i <= n; i++)
        printf("%d ", ans[i]);
    putchar('\n');
    return 0;
}