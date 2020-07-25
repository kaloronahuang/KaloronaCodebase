// FOJ5023.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 7e5 + 200, RANGE = 1e7 + 20;

typedef long long ll;

int n, m, ai[MAX_N], BLOCK, prime[MAX_N], tot;
ll ans, ansBox[MAX_N], prod[MAX_N];
bool vis[RANGE];
vector<int> primes[MAX_N];

struct queryInfo
{
    int l, r, id;
    bool operator<(const queryInfo &rhs) const
    {
        if ((l / BLOCK) == (rhs.l / BLOCK))
            return ((l / BLOCK) & 1) ? r < rhs.r : r > rhs.r;
        return (l / BLOCK) < (rhs.l / BLOCK);
    }
} queries[MAX_N];

void updatePrime(int x, int d)
{
    ans -= 1LL * prod[x] * prod[x];
    prod[x] += d;
    ans += 1LL * prod[x] * prod[x];
}

void update(int pos, int d)
{
    for (int x : primes[pos])
        updatePrime(x, d);
}

int main()
{
    freopen("sequence.in", "r", stdin);
    freopen("sequence.out", "w", stdout);
    scanf("%d%d", &n, &m), BLOCK = sqrt(n);
    for (int i = 2; i < RANGE; i++)
    {
        if (!vis[i])
            prime[++tot] = i;
        for (int j = 1; j <= tot && 1LL * i * prime[j] < RANGE; j++)
        {
            vis[i * prime[j]] = true;
            if (i % prime[j] == 0)
                break;
        }
    }
    for (int i = 1, acc; i <= n; i++)
    {
        scanf("%d", &ai[i]), acc = ai[i];
        for (int j = 1; j <= tot && 1LL * prime[j] * prime[j] <= acc; j++)
            if (acc % prime[j] == 0)
            {
                primes[i].push_back(j);
                while (acc % prime[j] == 0)
                    acc /= prime[j];
            }
        if (acc > 1)
            primes[i].push_back(lower_bound(prime + 1, prime + 1 + tot, acc) - prime);
    }
    for (int i = 1; i <= m; i++)
        scanf("%d%d", &queries[i].l, &queries[i].r), queries[i].id = i;
    // cerr << 1.0 * clock() / CLOCKS_PER_SEC << endl;
    sort(queries + 1, queries + 1 + m);
    int cl = 1, cr = 0;
    for (int i = 1; i <= m; i++)
    {
        queryInfo q = queries[i];
        while (q.l < cl)
            update(--cl, 1);
        while (cr < q.r)
            update(++cr, 1);
        while (q.l > cl)
            update(cl++, -1);
        while (cr > q.r)
            update(cr--, -1);
        ansBox[q.id] = ans;
    }
    for (int i = 1; i <= m; i++)
        printf("%lld\n", ansBox[i]);
    return 0;
}