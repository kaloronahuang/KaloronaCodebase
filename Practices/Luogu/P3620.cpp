// P3620.cpp
#include <iostream>
#include <cstdio>
#include <queue>
#define ll long long
using namespace std;
const int maxn = 202000;
ll prv[maxn], nxt[maxn], N, K, block[maxn], num, prvnum, ans;
struct node
{
    ll id, val;
    bool operator<(const node &nd) const
    {
        return val > nd.val;
    }
};
priority_queue<node> qpool;
bool vis[maxn];
int main()
{
    scanf("%lld%lld", &N, &K), scanf("%lld", &prvnum);
    for (int i = 1; i < N; i++)
    {
        scanf("%lld", &num);
        block[i] = num - prvnum, prvnum = num;
        prv[i] = i - 1, nxt[i] = i + 1;
    }
    nxt[N - 1] = 0;
    for (int i = 1; i < N; i++)
        qpool.push(node{i, block[i]});
    while (K--)
    {
        while (!qpool.empty() && block[qpool.top().id] != qpool.top().val)
            qpool.pop();
        if(qpool.empty())
            break;
        node curt = qpool.top();
        qpool.pop();
        int l = prv[curt.id], r = nxt[curt.id];
        ans += curt.val;
        block[curt.id] = prv[curt.id] && nxt[curt.id] ? min((ll)1e16, block[l] + block[r]) - block[curt.id] : 1e16;
        block[l] = block[r] = 1e16;
        prv[nxt[curt.id] = nxt[r]] = curt.id;
        nxt[prv[curt.id] = prv[l]] = curt.id;
        curt.val = block[curt.id];
        qpool.push(curt);
    }
    printf("%lld", ans);
    return 0;
}