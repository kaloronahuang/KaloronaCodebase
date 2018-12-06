// CH1812.cpp
#include <iostream>
#include <queue>
#define ll long long
using namespace std;
const int maxn = 100200;
ll arr[maxn], prev[maxn], nxt[maxn], N, M, merged[maxn];
bool vis[maxn];
struct node
{
    ll pid, val;
    bool operator<(const node &nd) const
    {
        return abs(val) > abs(nd.val);
    }
};
priority_queue<node> nds;
void del(ll p) { vis[p] = false, prev[nxt[p]] = prev[p], nxt[prev[p]] = nxt[p]; }
int main()
{
    scanf("%lld%lld", &N, &M);
    for (int i = 1; i <= N; i++)
        scanf("%d", &arr[i]);
    ll tot = 1;
    for (int i = 1; i <= N; i++)
        if (arr[i] * merged[tot] >= 0)
            merged[tot] += arr[i];
        else
            merged[++tot] = arr[i];
    ll ans = 0, cnt = 0;
    return 0;
}