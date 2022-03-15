// L.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 1e6 + 200;

int n, hi[MAX_N], ai[MAX_N], bi[MAX_N];
ll ans;

ll calc(int i, int j) { return 1LL * (hi[i] + hi[j]) * (j - i); }

// downhill, uphill;
// [l, r] stands for decision point collection for [L, R];
void solve(int l, int r, int L, int R)
{
    if (l > r)
        return;
    int mid = (l + r) >> 1, p = -1;
    ll pans = 0;
    for (int i = L; i <= R && ai[i] < bi[mid]; i++)
        if (calc(ai[i], bi[mid]) > pans)
            pans = calc(ai[i], bi[mid]), p = i;
    ans = max(ans, pans);
    solve(l, mid - 1, L, p), solve(mid + 1, r, p, R);
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &hi[i]);
    for (int i = 1; i <= n; i++)
        if (ai[0] == 0 || hi[ai[ai[0]]] < hi[i])
            ai[++ai[0]] = i;
    for (int i = n; i >= 1; i--)
        if (bi[0] == 0 || hi[bi[bi[0]]] < hi[i])
            bi[++bi[0]] = i;
    reverse(bi + 1, bi + 1 + bi[0]);
    solve(1, bi[0], 1, ai[0]), printf("%lld\n", ans);
    return 0;
}