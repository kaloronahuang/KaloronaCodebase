// BZ2038.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll MAX_N = 50100;
struct query
{
    ll l, r, id, answerSon, answerDom;
    bool operator<(const query &qy) const { return id < qy.id; }
} queries[MAX_N];

ll ci[MAX_N], n, m, len, btot, num[MAX_N], lft[MAX_N], rig[MAX_N], ans;

bool compare_left(query a, query b) { return a.l < b.l || (a.l == b.l && a.r < b.r); }
bool compare_right(query a, query b) { return a.r < b.r || (a.r == b.r && a.l < b.l); }
ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }

void change(ll x, ll w)
{
    ans -= num[x] * (num[x] - 1);
    num[x] += w;
    ans += num[x] * (num[x] - 1);
}

void simplify(ll id)
{
    ll d = gcd(queries[id].answerSon, queries[id].answerDom);
    if (!d)
        queries[id].answerSon = 0, queries[id].answerDom = 1;
    else
        queries[id].answerSon /= d, queries[id].answerDom /= d;
}

int main()
{
    scanf("%lld%lld", &n, &m);
    for (ll i = 1; i <= n; i++)
        scanf("%lld", &ci[i]);
    for (ll i = 1; i <= m; i++)
        scanf("%lld%lld", &queries[i].l, &queries[i].r), queries[i].id = i;

    len = sqrt(m), btot = m / len;
    sort(queries + 1, queries + 1 + m, compare_left);
    for (ll i = 1; i <= btot; i++)
        lft[i] = (i - 1) * len + 1, rig[i] = i * len;
    if (rig[btot] < m)
        lft[btot + 1] = rig[btot++] + 1, rig[btot] = m;

    for (ll i = 1; i <= btot; i++)
    {
        sort(queries + lft[i], queries + rig[i] + 1, compare_right);
        memset(num, 0, sizeof(num));
        ans = 0;
        // previous interval;
        ll l = queries[lft[i]].l, r = queries[lft[i]].r;
        // process the first query;
        for (ll j = l; j <= r; j++)
            change(ci[j], 1);
        queries[lft[i]].answerSon = ans;
        queries[lft[i]].answerDom = (queries[lft[i]].r - queries[lft[i]].l + 1) * (queries[lft[i]].r - queries[lft[i]].l);
        simplify(lft[i]);

        for (ll j = lft[i] + 1; j <= rig[i]; j++)
        {
            while (l < queries[j].l)
                change(ci[l++], -1);
            while (l > queries[j].l)
                change(ci[--l], 1);
            while (r < queries[j].r)
                change(ci[++r], 1);
            while (r > queries[j].r)
                change(ci[r--], -1);
            if (queries[j].l == queries[j].r)
                queries[j].answerSon = 0, queries[j].answerDom = 1;
            else
            {
                queries[j].answerSon = ans, queries[j].answerDom = (r - l) * (r - l + 1);
                simplify(j);
            }
        }
    }

    sort(queries + 1, queries + 1 + m);
    for (ll i = 1; i <= m; i++)
        printf("%lld/%lld\n", queries[i].answerSon, queries[i].answerDom);
    return 0;
}