// P2878.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 100100;

int n, seq[MAX_N], ti[MAX_N], di[MAX_N];

bool compare(int a, int b) { return 1LL * ti[a] * di[b] < 1LL * ti[b] * di[a]; }

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &ti[i], &di[i]), seq[i] = i;
    sort(seq + 1, seq + 1 + n, compare);
    ll ans = 0, prefix_time = 0;
    for (int i = 1; i <= n; i++)
        ans += 2LL * prefix_time * di[seq[i]], prefix_time += ti[seq[i]];
    printf("%lld", ans);
    return 0;
}