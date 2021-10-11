// D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

int T, n, m, ufs[MAX_N], siz[MAX_N];
char cmdlet[20];

int find(int x) { return ufs[x] == x ? x : ufs[x] = find(ufs[x]); }

void merge(int x, int y)
{
    int fx = find(x), fy = find(y);
    if (fx != fy)
        ufs[fx] = fy, siz[fy] += siz[fx];
}

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= (n << 1); i++)
            ufs[i] = i, siz[i] = (i <= n);
        for (int i = 1, u, v; i <= m; i++)
        {
            scanf("%d%d%s", &u, &v, cmdlet + 1);
            if (cmdlet[1] == 'i')
                merge(u, v + n), merge(u + n, v);
            else
                merge(u, v), merge(u + n, v + n);
        }
        bool flag = true;
        for (int i = 1; i <= n; i++)
            flag &= (find(i) != find(i + n));
        if (flag)
        {
            int ans = 0;
            for (int i = 1; i <= n; i++)
                if (find(i) == i)
                    ans += max(siz[find(i)], siz[find(i + n)]);
            for (int i = n + 1; i <= (n << 1); i++)
                if (find(i) == i)
                    ans += max(siz[find(i)], siz[find(i - n)]);
            ans >>= 1;
            printf("%d\n", ans);
        }
        else
            puts("-1");
    }
    return 0;
}