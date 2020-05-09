// P5330.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

typedef long long ll;

int P, Q, n, m, A[MAX_N], B[MAX_N], prefix[MAX_N], rnk[MAX_N], tot[MAX_N], key[MAX_N];
bool vis[MAX_N];
ll T;

int main()
{
    scanf("%d%d%d%d%lld", &P, &Q, &n, &m, &T);
    int len = Q / __gcd(P, Q);
    for (int i = 1; i <= n; i++)
        scanf("%d", &A[i]);
    for (int i = 1; i <= m; i++)
        scanf("%d", &B[i]), prefix[B[i]] = 1, key[B[i]] = 1;
    for (int start_pos = 0; start_pos < Q; start_pos++)
    {
        if (vis[start_pos])
            continue;
        int last_pos = start_pos;
        rnk[last_pos] = 1, vis[start_pos] = true;
        for (int curt = (start_pos + P) % Q; curt != start_pos; last_pos = curt, curt = (curt + P) % Q)
            vis[curt] = true, rnk[curt] = rnk[last_pos] + 1, prefix[curt] += prefix[last_pos];
        tot[start_pos] = prefix[last_pos];
        for (int curt = (start_pos + P) % Q; curt != start_pos; curt = (curt + P) % Q)
            tot[curt] = prefix[last_pos];
    }
    ll ans = 0;
    for (int i = 1; i <= n; i++)
    {
        if (A[i] >= T)
            continue;
        ll loop_cnt = (T - A[i] - 1) / P;
        ll lft = A[i] % Q, rig = (A[i] + loop_cnt % len * P) % Q;
        ans += loop_cnt / len * tot[lft];
        if (rnk[rig] >= rnk[lft])
            ans += prefix[rig] - prefix[lft] + key[lft];
        else
            ans += tot[lft] - (prefix[lft] - prefix[rig] - key[lft]);
    }
    printf("%lld\n", ans);
    return 0;
}