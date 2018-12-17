// CH4901.cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#define ll long long
const int maxn = 20020;
const int maxm = 100200;
using namespace std;
ll N, M, fa[maxn << 1];
struct relation
{
    ll u, v, w;
    bool operator<(const relation &rell) const
    {
        return w > rell.w;
    }
} rel[maxm];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void merge(int x, int y) { fa[find(x)] = find(y); }
int main()
{
    for (int i = 0; i < (maxn << 1); i++)
        fa[i] = i;
    scanf("%lld%lld", &N, &M);
    for (int i = 1; i <= M; i++)
        scanf("%lld%lld%lld", &rel[i].u, &rel[i].v, &rel[i].w);
    sort(rel + 1, rel + 1 + M);
    for (int i = 1; i <= M; i++)
    {
        int nu = rel[i].u, au = rel[i].u + N;
        int nv = rel[i].v, neov = rel[i].v + N;
        if (find(nu) == find(nv))
        {
            printf("%lld", rel[i].w);
            return 0;
        }
        merge(nu, neov);
        merge(nv, au);
    }
    printf("0");
    return 0;
}