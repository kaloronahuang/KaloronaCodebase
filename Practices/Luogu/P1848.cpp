// P1848.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 1e5 + 200;

ll n, m, hi[MAX_N], wi[MAX_N], q[MAX_N], f[MAX_N], head, tail, ans;
multiset<ll> S;
bool vis[MAX_N];

int main()
{
    scanf("%lld%lld", &n, &m);
    head = 1, tail = ans = 0;
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld%lld", &hi[i], &wi[i]);
        for (q[++tail] = i - 1; head < tail && hi[i] > hi[q[tail]]; tail--)
            S.erase(S.find(f[q[tail - 1]] + hi[q[tail]]));
        S.insert(f[q[tail]] + hi[i]);
        q[tail + 1] = i;
        for (ans += wi[i]; ans > m; ans -= wi[q[head]])
        {
            S.erase(S.find(f[q[head]] + hi[q[head + 1]]));
            if (++q[head] == q[head + 1])
                ++head;
            else
                S.insert(f[q[head]] + hi[q[head + 1]]);
        }
        f[i] = *S.begin();
    }
    printf("%lld", f[n]);
    return 0;
}