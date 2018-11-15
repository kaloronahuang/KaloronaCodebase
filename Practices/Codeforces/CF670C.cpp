// CF670C.cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;
const int maxn = 200200;
int a[maxn], b[maxn], c[maxn], n, m, misc[maxn], ana[maxn], anb[maxn];
int new_siz = 1;
struct film
{
    int pleased, almost;
    film()
    {
        pleased = 0, almost = 0;
    }
} films[maxn];
int query(int x)
{
    return (lower_bound(misc + 1, misc + 1 + new_siz, x) - (misc + 1));
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]), misc[i] = a[i];
    scanf("%d", &m);
    for (int i = 1; i <= m; i++)
        scanf("%d", &b[i]);
    for (int i = 1; i <= m; i++)
        scanf("%d", &c[i]);
    sort(a + 1, a + 1 + n);
    for (int i = 1; i <= n; i++)
        if (i == 1 || a[i] != a[i - 1])
            misc[new_siz++] = a[i];
    for (int i = 1; i <= n; i++)
        ana[query(a[i])]++, anb[query(b[i])]++;
    int stda = 0;
    int stdb = 0;
    int idx = 0;
    for (int i = 1; i <= m; i++)
        if (ana[query(b[i])] > stda)
            idx = i, stda = ana[query(b[i])], stdb = anb[query(c[i])];
        else if (ana[query(b[i])] == stda && anb[query(c[i])] >= stdb)
            idx = i, stdb = anb[query(c[i])];
    printf("%d", idx);
    return 0;
}