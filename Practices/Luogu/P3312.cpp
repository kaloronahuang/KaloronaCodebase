// P3312.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAX_Q = 2e4 + 2000, MAX_N = 1e5 + 2000;

int mu[MAX_N], g[MAX_N], prime[MAX_N], ptot, tree[MAX_N], T, answers[MAX_N];
pair<int, int> f[MAX_N];
bool isNotPrime[MAX_N];

int lowbit(int x) { return x & (-x); }

void update(int x, int d)
{
    while (x < MAX_N)
        tree[x] += d, x += lowbit(x);
}

int ask(int x)
{
    int ans = 0;
    while (x)
        ans += tree[x], x -= lowbit(x);
    return ans;
}

struct query
{
    ll id, n, m, limit;
    bool operator<(const query &q) const { return limit < q.limit; }
    int solve()
    {
        int res = 0;
        for (int i = 1, pos; i <= n; i = pos + 1)
        {
            pos = min(n / (n / i), m / (m / i));
            res += (ask(pos) - ask(i - 1)) * (n / i) * (m / i);
        }
        return res;
    }
} queries[MAX_Q];

void preprocess()
{
    mu[1] = 1, f[1] = make_pair(1, 1);
    for (int i = 2; i < MAX_N; i++)
    {
        if (!isNotPrime[i])
            prime[++ptot] = i, mu[i] = -1, g[i] = i + 1, f[i] = make_pair(i + 1, i);
        for (int j = 1; j <= ptot && i * prime[j] < MAX_N; j++)
        {
            isNotPrime[i * prime[j]] = true;
            if (i % prime[j] == 0)
            {
                mu[i * prime[j]] = 0;
                g[i * prime[j]] = g[i] * prime[j] + 1;
                f[i * prime[j]] = make_pair(f[i].first / g[i] * g[i * prime[j]], i * prime[j]);
                break;
            }
            mu[i * prime[j]] = -mu[i];
            f[i * prime[j]] = make_pair(f[i].first * f[prime[j]].first, i * prime[j]);
            g[i * prime[j]] = prime[j] + 1;
        }
    }
}

int main()
{
    preprocess();
    sort(f + 1, f + 1 + MAX_N);
    scanf("%d", &T);
    for (int i = 1; i <= T; i++)
    {
        queries[i].id = i;
        scanf("%d%d%d", &queries[i].n, &queries[i].m, &queries[i].limit);
        if (queries[i].n > queries[i].m)
            swap(queries[i].n, queries[i].m);
    }
    sort(queries + 1, queries + 1 + T);
    for (int i = 1, j = 1; i <= T; i++)
    {
        while (f[j].first <= queries[i].limit && j <= MAX_N)
        {
            for (int k = f[j].second; k < MAX_N; k += f[j].second)
                update(k, f[j].first * mu[k / f[j].second]);
            j++;
        }
        answers[queries[i].id] = queries[i].solve();
    }
    for (int i = 1; i <= T; i++)
        printf("%d\n", answers[i] & (~(1 << 31)));
    return 0;
}