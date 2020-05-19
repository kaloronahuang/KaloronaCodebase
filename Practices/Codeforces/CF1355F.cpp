// CF1355F.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 4e4 + 200;

int T, primes[MAX_N], tot;
bool vis[MAX_N];

struct node
{
    ll curt, cnt, base;
    bool operator<(const node &rhs) const { return cnt < rhs.cnt || (cnt == rhs.cnt && curt > rhs.curt); }
};

ll query(ll x, ll ret = 0)
{
    printf("? %lld\n", x), fflush(stdout), scanf("%lld", &ret);
    return ret;
}

int main()
{
    for (int i = 2; i < MAX_N; i++)
    {
        if (!vis[i])
            primes[++tot] = i;
        for (int j = 1; j <= tot && 1LL * i * primes[j] < MAX_N; j++)
        {
            vis[i * primes[j]] = true;
            if (i % primes[j] == 0)
                break;
        }
    }
    scanf("%d", &T);
    while (T--)
    {
        priority_queue<node> pq;
        for (int i = 1; i <= tot; i++)
            pq.push(node{primes[i], 1, primes[i]});
        ll ans = 1;
        for (int cid = 1; cid <= 22; cid++)
        {
            ll x = 1;
            vector<node> bucket;
            while (!pq.empty())
            {
                node u = pq.top();
                pq.pop();
                if (1.0 * x * u.curt > 1e18)
                {
                    pq.push(u);
                    break;
                }
                x *= u.curt, bucket.push_back(u);
            }
            ll res = query(x);
            for (node u : bucket)
                if (res % u.curt == 0)
                {
                    ans /= u.cnt, u.cnt++, ans *= u.cnt;
                    u.curt *= u.base, pq.push(u);
                }
        }
        printf("! %lld\n", 2LL * ans), fflush(stdout);
    }
    return 0;
}