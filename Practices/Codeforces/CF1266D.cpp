// CF1266D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, MAX_E = 3e5 + 200;

typedef long long ll;

int n, m;
ll flow[MAX_N];
deque<int> in, out, ans[2];
deque<ll> ans2;

int main()
{
    scanf("%d%d", &n, &m);
    while (m--)
    {
        int u, v, d;
        scanf("%d%d%d", &u, &v, &d), flow[u] += d, flow[v] -= d;
    }
    for (int i = 1; i <= n; i++)
        if (flow[i] > 0)
            out.push_back(i); // loan sender;
        else if (flow[i] < 0)
            in.push_back(i); // loan reciver;
    while ((!in.empty()) && (!out.empty()))
    {
        ll v = min(flow[out.front()], -flow[in.front()]);
        flow[out.front()] -= v, flow[in.front()] += v;
        ans[0].push_back(out.front()), ans[1].push_back(in.front()), ans2.push_back(v);
        if (flow[out.front()] == 0)
            out.pop_front();
        if (flow[in.front()] == 0)
            in.pop_front();
    }
    printf("%lld\n", 1LL * ans[0].size());
    for (int i = 0, siz = ans[0].size(); i < siz; i++)
        printf("%d %d %lld\n", ans[0][i], ans[1][i], ans2[i]);
    return 0;
}