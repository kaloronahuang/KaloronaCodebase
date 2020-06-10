// P3149.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e5 + 200;

typedef long long ll;
typedef pair<int, int> pii;

int n, m, ai[MAX_N], rk[MAX_N], nodes[MAX_N], prod[MAX_N];
ll pre[MAX_N];
pii rnds[MAX_N];
vector<int> mp;

inline int lowbit(int x) { return x & (-x); }

int ripe(int x) { return lower_bound(mp.begin(), mp.end(), x) - mp.begin() + 1; }

void update(int x, int d)
{
    for (; x <= n; x += lowbit(x))
        nodes[x] += d;
}

int query(int x, int ret = 0)
{
    for (; x; x -= lowbit(x))
        ret += nodes[x];
    return ret;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]), rnds[i] = make_pair(ai[i], i);
    sort(rnds + 1, rnds + 1 + n, [](const pii &rhs1, const pii &rhs2) { return rhs1.first == rhs2.first ? rhs1.second > rhs2.second : rhs1.first < rhs2.first; });
    for (int i = 1; i <= n; i++)
        rk[rnds[i].second] = i;
    for (int i = 1; i <= n; i++)
        update(n - rnds[i].second + 1, 1), prod[rnds[i].second] = query((n - rnds[i].second + 1) - 1);
    for (int i = 1; i <= n; i++)
        rnds[i] = make_pair(rk[i], prod[i]);
    sort(rnds + 1, rnds + 1 + n);
    for (int i = n - 1; i >= 0; i--)
        pre[i] = pre[i + 1] + rnds[i + 1].second;
    printf("%lld\n", pre[0]);
    int max_q = -0x3f3f3f3f;
    ll preans = pre[0];
    while (m--)
    {
        int k;
        scanf("%d", &k);
        //printf("%d ", rk[k]);
        if (rk[k] >= max_q)
            printf("%lld\n", pre[rk[k]]), max_q = rk[k], preans = pre[rk[k]];
        else
            printf("%lld\n", preans);
    }
    return 0;
}