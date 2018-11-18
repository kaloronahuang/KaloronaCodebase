// CF670C.cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;
const int maxn = 200200;
int a[maxn], b[maxn], c[maxn], n, m, misc[maxn << 2], lang[maxn], mlang[maxn];
int new_siz, msiz;
int query(int x)
{
    return (lower_bound(mlang + 1, mlang + msiz + 1, x) - mlang);
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]), misc[++new_siz] = a[i];
    scanf("%d", &m);
    for (int i = 1; i <= m; i++)
        scanf("%d", &b[i]), misc[++new_siz] = b[i];
    for (int i = 1; i <= m; i++)
        scanf("%d", &c[i]), misc[++new_siz] = c[i];

    sort(misc + 1, misc + 1 + new_siz);

    for (int i = 1; i <= new_siz; i++)
        if (i == 1 || misc[i] != misc[i - 1])
            mlang[++msiz] = misc[i];

    for (int i = 1; i <= n; i++)
        lang[query(a[i])]++;
    int stat1 = -1, stat2 = -1, id = 0;
    for (int i = 1; i <= m; i++)
        if (lang[query(b[i])] > stat1)
            id = i, stat1 = lang[query(b[i])], stat2 = lang[query(c[i])];
        else if (lang[query(b[i])] == stat1 && lang[query(c[i])] > stat2)
            id = i, stat2 = lang[query(c[i])];
    printf("%d", id);
    return 0;
}