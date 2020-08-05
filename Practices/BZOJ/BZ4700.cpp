// BZ4700.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 3e5 + 200;

int n, atk, q[MAX_N], head, tail;
ll pred[MAX_N], sufa[MAX_N], dp[MAX_N];

struct robot
{
    int ai, di;
    bool operator<(const robot &rhs) const { return 1LL * di * rhs.ai < 1LL * rhs.di * ai; }
} rbts[MAX_N];

struct tup
{
    int opt, id;
    ll val;
} ai[MAX_N], bi[MAX_N], tmp;

bool cmp_typ_a(const tup &rhs1, const tup &rhs2) { return rhs1.opt < rhs2.opt || (rhs1.opt == rhs2.opt && rhs1.val < rhs2.val); }

bool cmp_typ_b(const tup &rhs1, const tup &rhs2) { return rhs1.opt > rhs2.opt; }

void solve(int l, int r)
{
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    solve(l, mid), solve(mid + 1, r);
    head = 1, tail = 0;
    for (int i = l; i <= mid; i++)
    {
        while (head <= tail && ai[i].opt == ai[q[tail]].opt)
            tail--;
        while (head < tail && (ai[i].val - ai[q[tail]].val) * (ai[q[tail]].opt - ai[q[tail - 1]].opt) >= (ai[q[tail]].val - ai[q[tail - 1]].val) * (ai[i].opt - ai[q[tail]].opt))
            tail--;
        q[++tail] = i;
    }
    for (int i = mid + 1; i <= r; i++)
    {
        while (head < tail && bi[i].val + ai[q[head]].val - bi[i].opt * ai[q[head]].opt < bi[i].val + ai[q[head + 1]].val - bi[i].opt * ai[q[head + 1]].opt)
            head++;
        dp[bi[i].id] = max(dp[bi[i].id], bi[i].val + ai[q[head]].val - bi[i].opt * ai[q[head]].opt);
    }
    sort(ai + l, ai + 1 + r, cmp_typ_a);
    sort(bi + l, bi + 1 + r, cmp_typ_b);
}

int main()
{
    scanf("%d%d", &n, &atk);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &rbts[i].ai, &rbts[i].di), rbts[i].di = (rbts[i].di - 1) / atk + 1;
    sort(rbts + 1, rbts + 1 + n);
    for (int i = 1; i <= n; i++)
        pred[i] = pred[i - 1] + rbts[i].di;
    for (int i = n; i >= 1; i--)
        sufa[i] = sufa[i + 1] + rbts[i].ai;
    ll sum = 0;
    for (int i = 1; i <= n; i++)
    {
        sum += 1LL * rbts[i].di * sufa[i] - rbts[i].ai;
        ll vi = rbts[i].di * sufa[i] + rbts[i].ai * (pred[i - 1] - 1);
        ai[i] = tup{rbts[i].di, i, vi};
        bi[i] = tup{rbts[i].ai, i, vi};
    }
    ll ans = sum;
    solve(1, n);
    for (int i = 1; i <= n; i++)
        ans = min(ans, sum - dp[i]);
    printf("%lld\n", ans);
    return 0;
}