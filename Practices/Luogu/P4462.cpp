// P4462.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200, block = sqrt(MAX_N);

typedef long long ll;

int n, m, target, ai[MAX_N];
int bucket[MAX_N];
ll ansBox[MAX_N];

struct queryInfo
{
    int l, r, id;
    bool operator<(const queryInfo &rhs) const { return l / block == rhs.l / block ? (((l / block) & 1) ? r < rhs.r : r > rhs.r) : l / block < rhs.l / block; }
} queries[MAX_N];

int main()
{
    scanf("%d%d%d", &n, &m, &target);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]), ai[i] ^= ai[i - 1];
    for (int i = 1; i <= m; i++)
        scanf("%d%d", &queries[i].l, &queries[i].r), queries[i].l--, queries[i].id = i;
    sort(queries + 1, queries + 1 + m);
    int cl = 0, cr = 0;
    bucket[0]++;
    ll ans = 0;
    for (int i = 1; i <= m; i++)
    {
        while (cl < queries[i].l)
            bucket[ai[cl]]--, ans -= bucket[target ^ ai[cl]], cl++;
        while (cl > queries[i].l)
            cl--, ans += bucket[target ^ ai[cl]], bucket[ai[cl]]++;
        while (cr > queries[i].r)
            bucket[ai[cr]]--, ans -= bucket[target ^ ai[cr]], cr--;
        while (cr < queries[i].r)
            cr++, ans += bucket[target ^ ai[cr]], bucket[ai[cr]]++;
        ansBox[queries[i].id] = ans;
    }
    for (int i = 1; i <= m; i++)
        printf("%lld\n", ansBox[i]);
    return 0;
}