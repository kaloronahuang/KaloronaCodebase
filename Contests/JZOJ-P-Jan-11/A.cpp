// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;
typedef long long ll;
typedef pair<ll, ll> pii;

ll L, n, m, wi[MAX_N], di[MAX_N];
struct node
{
    ll x, y;
    node() {}
    node(ll x_, ll y_) : x(x_), y(y_) {}
    bool operator<(const node &rhs) const { return x > rhs.x || (x == rhs.x && y > rhs.y); }
};
priority_queue<node> pq;
ll ai[MAX_N * 10], bi[MAX_N * 10];

void fileIO()
{
    freopen("laundry.in", "r", stdin);
    freopen("laundry.out", "w", stdout);
}

int main()
{
    fileIO();
    scanf("%lld%lld%lld", &L, &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &wi[i]), pq.push(node(wi[i], wi[i]));
    for (int i = 1; i <= m; i++)
        scanf("%lld", &di[i]);
    // process for wi;
    for (ll i = 1, x, y; i <= L; i++)
    {
        x = pq.top().x, y = pq.top().y;
        ai[i] = x;
        pq.pop(), pq.push(node(ai[i] + y, y));
    }
    while (!pq.empty())
        pq.pop();
    for (int i = 1; i <= m; i++)
        pq.push(node(di[i], di[i]));
    for (ll i = 1, x, y; i <= L; i++)
    {
        x = pq.top().x, y = pq.top().y;
        bi[i] = x;
        pq.pop(), pq.push(node(bi[i] + y, y));
    }
    ll ans = 0;
    for (int i = 1; i <= L; i++)
        ans = max(ans, ai[i] + bi[L - i + 1]);
    printf("%lld\n", ans);
    return 0;
}