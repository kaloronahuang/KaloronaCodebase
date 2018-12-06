// CH1812.cpp
#include <iostream>
#include <queue>
#include <cstdio>
#include <cstring>
#include <cmath>
#define ll long long
using namespace std;
const int maxn = 100200;
ll arr[maxn], prv[maxn], nxt[maxn], N, M, merged[maxn];
bool vis[maxn];
struct node
{
    ll pid, val;
    node() {}
    node(ll pd, ll v) { pid = pd, val = v; }
    bool operator<(const node &nd) const { return abs(val) > abs(nd.val); }
};
priority_queue<node> nds;
void del(ll p) { vis[p] = false, prv[nxt[p]] = prv[p], nxt[prv[p]] = nxt[p]; }
int main()
{
    scanf("%lld%lld", &N, &M);
    for (int i = 1; i <= N; i++)
        scanf("%lld", &arr[i]);
    ll tot = 1;
    // merge them to one.
    for (int i = 1; i <= N; i++)
        if (arr[i] * merged[tot] >= 0)
            merged[tot] += arr[i];
        else
            merged[++tot] = arr[i];
    ll ans = 0, cnt = 0;
    for (int i = 1; i <= tot; i++)
    {
        nds.push(node((ll)i, merged[i]));
        if (merged[i] > 0)
            ans += merged[i], cnt++;
        prv[i] = i - 1, nxt[i] = i + 1;
    }
    memset(vis, true, sizeof(vis));
    while (cnt > M)
    {
        cnt--;
        node curt = nds.top();
        while (!vis[curt.pid])
            nds.pop(), curt = nds.top();
        nds.pop();
        int i = curt.pid;
        if (prv[i] && nxt[i] != tot + 1)
            ans -= abs(merged[i]);
        else if (merged[i] > 0)
            ans -= merged[i];
        else
        {
            cnt++;
            continue;
        }
        merged[i] += merged[prv[i]] + merged[nxt[i]];
        del(prv[i]), del(nxt[i]);
        curt.val = merged[i], nds.push(curt);
    }
    printf("%lld", ans);
    return 0;
}