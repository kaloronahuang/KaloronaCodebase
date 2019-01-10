// Z.cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <deque>
#include <algorithm>
#define ll long long
using namespace std;
const ll MAX_N = 2e5 + 200;
ll n, h[MAX_N], dp[MAX_N], C, q[MAX_N], head, tail;
ll pow2(ll base) { return base * base; }
double calc(ll a, ll b) { return 1.0 * (dp[a] - dp[b] + pow2(h[a]) - pow2(h[b])) / (h[a] - h[b]); }
int main()
{
    scanf("%lld%lld", &n, &C);
    for (ll i = 1; i <= n; i++)
        scanf("%lld", &h[i]);
    q[++tail] = 1;
    for (ll i = 2; i <= n; i++)
    {
        while (head < tail && calc(q[head], q[head + 1]) <= 2 * h[i])
            head++;
        dp[i] = pow2(h[i] - h[q[head]]) + dp[q[head]] + C;
        while (head < tail && calc(q[tail], q[tail - 1]) > calc(i, q[tail]))
            tail--;
        q[++tail] = i;
    }
    printf("%lld", dp[n]);
    return 0;
}