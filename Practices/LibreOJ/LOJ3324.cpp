// LOJ3324.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 110;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int T, cnt;
ll n, k, fib[MAX_N], g[MAX_N], ans;

void solve(int b)
{
    if (k > g[b])
        ans++;
    for (int i = 0; i < b; i++)
        if (k > g[i])
            ans += fib[b - i];
}

int main()
{
    fib[1] = g[1] = 1, cnt = 1;
    for (int i = 2; i < MAX_N; i++)
    {
        fib[i] = fib[i - 1] + fib[i - 2];
        g[i] = g[i - 1] + g[i - 2] + 1, cnt++;
        if (g[i] > INF)
            break;
    }
    scanf("%d", &T);
    while (T--)
    {
        scanf("%lld%lld", &k, &n);
        if (n == 1)
        {
            puts("0");
            continue;
        }
        n -= 2, ans = 0;
        for (int i = cnt; i >= 0; i--)
            if (n >= g[i])
                solve(i), n -= g[i] + 1;
        printf("%lld\n", ans);
    }
    return 0;
}