// CH2401.cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define ll long long
const int maxn = 50;
ll W, N, arr[maxn], ans = 0, siz;
vector<ll> poss;
void dfs1(int pos, ll prev)
{
    if (!pos)
    {
        poss.push_back(prev);
        return;
    }
    dfs1(pos - 1, prev);
    if (prev + arr[pos] <= W)
        dfs1(pos - 1, prev + arr[pos]);
}
void dfs2(int pos, ll prev)
{
    if (pos == N + 1)
    {
        ll num = *--upper_bound(poss.begin(), poss.end(), W - prev);
        ans = max(ans, num + prev);
        return;
    }
    dfs2(pos + 1, prev);
    if (prev + arr[pos] <= W)
        dfs2(pos + 1, prev + arr[pos]);
}
bool cmp(ll a, ll b)
{
    return a > b;
}
int main()
{
    scanf("%lld%lld", &W, &N);
    for (int i = 1; i <= N; i++)
        scanf("%lld", &arr[i]);
    sort(arr + 1, arr + 1 + N, cmp);
    dfs1((N / 2), 0);
    sort(poss.begin(), poss.end());
    poss.erase(unique(poss.begin(), poss.end()), poss.end());
    siz = poss.size();
    dfs2((N / 2) + 1, 0);
    printf("%d", ans);
    return 0;
}