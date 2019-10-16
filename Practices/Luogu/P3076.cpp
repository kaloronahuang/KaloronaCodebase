// P3076.cpp
#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const int MAX_N = 1e5 + 200;

int n, m, xi[MAX_N], yi[MAX_N];
ll ans;

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &xi[i], &yi[i]), ans += abs(xi[i] - yi[i]);
    xi[++n] = m, yi[n] = 0;
    sort(xi + 1, xi + 1 + n), sort(yi + 1, yi + 1 + n);
    for (int i = 1; i <= n; i++)
        ans += abs(xi[i] - yi[i]);
    printf("%lld", ans);
    return 0;
}