// F.cpp
#include <bits/stdc++.h>
#define ll long long
#define pr pair<ll, ll>
using namespace std;
const int MAX_N = 101000;
pair<ll, ll> prs[MAX_N];
ll n, tmpx, tmpy, q[MAX_N], tot;
bool check(int a, int b, int c)
{
    ll x1 = prs[b].first - prs[a].first, y1 = prs[b].second - prs[a].second;
    ll x2 = prs[c].first - prs[b].first, y2 = prs[c].second - prs[b].second;
    return x1 * y2 - x2 * y1 >= 0;
}
int main()
{
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld%lld", &tmpx, &tmpy);
        prs[i].first = tmpx, prs[i].second = tmpy - tmpx * tmpx;
    }
    sort(prs + 1, prs + 1 + n);
    for (int i = 1; i <= n; i++)
    {
        while (tot >= 1 && prs[q[tot]].first == prs[i].first)
            tot--;
        while (tot >= 2 && check(q[tot - 1], q[tot], i))
            tot--;
        q[++tot] = i;
    }
    printf("%d", tot - 1);
    return 0;
}