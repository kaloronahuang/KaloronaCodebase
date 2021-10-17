// K.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

typedef long long ll;
typedef pair<int, int> pii;

int n, m, Q, T, siz[MAX_N], ufs[MAX_N];
pii queries[MAX_N];
ll answer, ansBox[MAX_N];

struct edge
{
    int src, dst, strength;
    bool operator<(const edge &lhs) const { return strength < lhs.strength; }
} edges[MAX_N];

int find(int x) { return ufs[x] == x ? x : ufs[x] = find(ufs[x]); }

void merge(int x, int y)
{
    int fx = find(x), fy = find(y);
    if (fx != fy)
    {
        answer -= ((1LL * siz[fx] * (siz[fx] - 1)) >> 1);
        answer -= ((1LL * siz[fy] * (siz[fy] - 1)) >> 1);
        siz[fx] += siz[fy], ufs[fy] = fx;
        answer += ((1LL * siz[fx] * (siz[fx] - 1)) >> 1);
    }
}

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d%d", &n, &m, &Q), answer = 0;
        for (int i = 1; i <= n; i++)
            ufs[i] = i, siz[i] = 1;
        for (int i = 1; i <= m; i++)
            scanf("%d%d%d", &edges[i].src, &edges[i].dst, &edges[i].strength);
        sort(edges + 1, edges + 1 + m);
        for (int i = 1; i <= Q; i++)
            scanf("%d", &queries[i].first), queries[i].second = i;
        sort(queries + 1, queries + 1 + Q);
        int ptr = m;
        for (int i = Q; i >= 1; i--)
        {
            while (ptr >= 1 && edges[ptr].strength >= queries[i].first)
                merge(edges[ptr].src, edges[ptr].dst), ptr--;
            ansBox[queries[i].second] = answer;
        }
        for (int i = 1; i <= Q; i++)
            printf("%lld\n", ansBox[i]);
    }
    return 0;
}