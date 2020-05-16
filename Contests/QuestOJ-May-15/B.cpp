// B.cpp
#include <bits/stdc++.h>
#include <ext/pb_ds/priority_queue.hpp>

using namespace std;

const int MAX_N = 3e4 + 200;

typedef long long ll;

int n, wi[MAX_N], tag[MAX_N], siz[MAX_N], mem[MAX_N], up[MAX_N], cnt[MAX_N];
ll dp[MAX_N], sum[MAX_N];
double real_val[MAX_N];
vector<int> G[MAX_N];

int find(int x) { return x == mem[x] ? x : mem[x] = find(mem[x]); }

void dfs(int u, int fa)
{
    up[u] = fa;
    for (int v : G[u])
        if (v != fa)
            dfs(v, u);
}

int main()
{
    scanf("%d", &n);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), G[u].push_back(v), G[v].push_back(u);
    ll ans = 0;
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &wi[i], &tag[i]);
    for (int rt = 1; rt <= n; rt++)
        if (tag[rt])
        {
            dfs(rt, 0);
            ll tot_sum = 0;
            for (int i = 1; i <= n; i++)
                mem[i] = i, siz[i] = 1, sum[i] = wi[i], tot_sum += wi[i];
            typedef pair<double, int> pii;
            typedef __gnu_pbds::priority_queue<pii, std::greater<pii>> heap;
            heap pq;
            static heap::point_iterator it[MAX_N];
            for (int i = 1; i <= n; i++)
                if (i != rt)
                    it[i] = pq.push(make_pair(1.0 * sum[i], i));
            while (!pq.empty())
            {
                pii u = pq.top();
                pq.pop();
                int v = find(up[u.second]);
                tot_sum += 1LL * siz[v] * sum[u.second];
                mem[u.second] = v, siz[v] += siz[u.second], sum[v] += sum[u.second];
                if (v != rt)
                    pq.modify(it[v], make_pair(double(sum[v]) / double(siz[v]), v));
            }
            ans = max(ans, tot_sum);
        }
    printf("%lld\n", ans);
    return 0;
}