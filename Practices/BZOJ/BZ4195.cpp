// BZ4195.cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
const int maxn = 1000200;
int n, T, mem[maxn], us[maxn], vs[maxn], es[maxn];
vector<int> mapping;
void init()
{
    for (int i = 0; i < maxn; i++)
        mem[i] = i;
}
int find(int x)
{
    return x == mem[x] ? x : mem[x] = find(mem[x]);
}
void merge(int a, int b)
{
    int rx = find(a), ry = find(b);
    if (rx != ry)
        mem[rx] = mem[ry];
}
int getId(int num)
{
    return lower_bound(mapping.begin(), mapping.end(), num) - mapping.begin();
}
int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n);
        init();
        for (int i = 1; i <= n; i++)
            scanf("%d%d%d", &us[i], &vs[i], &es[i]), mapping.push_back(us[i]), mapping.push_back(vs[i]);
        sort(mapping.begin(), mapping.end());
        mapping.erase(unique(mapping.begin(), mapping.end()), mapping.end());
        for (int i = 1; i <= n; i++)
            if (es[i] == 1)
                merge(getId(us[i]), getId(vs[i]));
        for (int i = 1; i <= n; i++)
            if (es[i] == 0 && (find(getId(us[i])) == find(getId(vs[i]))))
            {
                printf("NO\n");
                goto gt;
            }
        printf("YES\n");
    gt:
        continue;
    }
    return 0;
}