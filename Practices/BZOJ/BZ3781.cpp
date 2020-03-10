// BZ3781.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 50100;

typedef long long ll;

int n, m, limit, aff[MAX_N], ai[MAX_N], bucket[MAX_N], siz;
ll ans, ansBox[MAX_N];

struct query
{
    int l, r, id;
    bool operator<(const query &rhs) const { return aff[l] == aff[rhs.l] ? ((aff[l] & 1) ? r < rhs.r : r > rhs.r) : l < rhs.l; }
} queries[MAX_N];

ll pow2(ll x) { return x * x; }

void modify(int pos, int opt)
{
    ans -= pow2(bucket[ai[pos]]);
    bucket[ai[pos]] += opt;
    ans += pow2(bucket[ai[pos]]);
}

int main()
{
    scanf("%d%d%d", &n, &m, &limit), siz = sqrt(n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]), aff[i] = (i - 1) / siz + 1;
    for (int i = 1; i <= m; i++)
        scanf("%d%d", &queries[i].l, &queries[i].r), queries[i].id = i;
    sort(queries + 1, queries + 1 + m);
    int l = 1, r = 0;
    for (int i = 1; i <= m; i++)
    {
        while (l > queries[i].l)
            modify(--l, 1);
        while (r < queries[i].r)
            modify(++r, 1);
        while (l < queries[i].l)
            modify(l++, -1);
        while (r > queries[i].r)
            modify(r--, -1);
        ansBox[queries[i].id] = ans;
    }
    for (int i = 1; i <= m; i++)
        printf("%lld\n", ansBox[i]);
    return 0;
}