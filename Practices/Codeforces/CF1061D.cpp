// CF1061D.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 2e5 + 200, mod = 1e9 + 7;

ll n, x, y;

struct segment
{
    ll l, r;
} segs[MAX_N];

struct event
{
    ll pos, id, val;
    bool operator<(const event &target) const { return pos == target.pos ? val < target.val : pos < target.pos; }
} events[MAX_N << 1];

int main()
{
    scanf("%lld%lld%lld", &n, &x, &y);
    for (int i = 1; i <= n; i++)
        scanf("%lld%lld", &segs[i].l, &segs[i].r), events[(i << 1) - 1] = {segs[i].l, i, 0}, events[i << 1] = {segs[i].r, i, 1};
    sort(events + 1, events + 1 + (n << 1));
    stack<ll> st;
    ll ans = 0;
    for (int i = 1; i <= (n << 1); i++)
        if (events[i].val)
            st.push(events[i].pos);
        else
        {
            ll rbound = segs[events[i].id].r, lbound;
            if (st.empty())
                ans = (ans + x + y * (rbound - events[i].pos) % mod) % mod;
            else
            {
                lbound = st.top();
                if (y * (rbound - lbound) < x + y * (rbound - events[i].pos))
                    ans = (ans + y * (rbound - lbound) % mod) % mod, st.pop();
                else
                    ans = (ans + x + y * (rbound - events[i].pos) % mod) % mod;
            }
        }
    printf("%lld", ans);
    return 0;
}