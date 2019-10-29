// CF1159C.cpp
#include <bits/stdc++.h>
#define ll long long
#define pr pair<int, int>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, m, ai[MAX_N], bi[MAX_N], cnt[MAX_N];
ll ans;

int main()
{
    int mx_val = 0;
    scanf("%d%d", &n, &m);
    priority_queue<pr> pq;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &ai[i]), ans += 1LL * ai[i] * m, cnt[i] = m, mx_val = max(mx_val, ai[i]);
        pq.push(make_pair(ai[i], i));
    }
    for (int i = 1; i <= m; i++)
    {
        scanf("%d", &bi[i]);
        if (bi[i] < mx_val)
            puts("-1"), exit(0);
    }
    sort(bi + 1, bi + 1 + m);
    for (int i = m; i >= 1; i--)
    {
        while (!pq.empty() && cnt[pq.top().second] < 2 && pq.top().first < bi[i])
            pq.pop();
        if (pq.empty())
            puts("-1"), exit(0);
        pair<int, int> p = pq.top();
        cnt[p.second]--, ans += bi[i] - p.first, pq.pop(), pq.push(p);
    }
    printf("%lld", ans);
    return 0;
}