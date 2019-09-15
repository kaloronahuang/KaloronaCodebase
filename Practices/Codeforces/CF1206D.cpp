// CF1206D.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 1e5 + 200;

ll n, cnt[MAX_N], matrix[150][150], dist[150][150], tot, ai[MAX_N];

int main()
{
    scanf("%d", &n);
    for (ll i = 1, tmp; i <= n; i++)
    {
        scanf("%lld", &tmp);
        if (tmp)
            ai[++tot] = tmp;
    }
    if (tot >= 150)
        puts("3"), exit(0);
    for (int i = 1; i <= tot; i++)
        for (int j = 1; j <= tot; j++)
            if ((ai[i] & ai[j]) != 0 && i != j)
                matrix[i][j] = dist[i][j] = 1;
            else
                matrix[i][j] = dist[i][j] = 1e9;

    // graph contructed;
    ll ans = 1e9;
    for (int k = 1; k <= tot; k++)
    {
        for (int i = 1; i <= tot; i++)
            for (int j = i + 1; j <= tot; j++)
                ans = min(ans, dist[i][j] + matrix[i][k] + matrix[k][j]);
        for (int i = 1; i <= tot; i++)
            for (int j = 1; j <= tot; j++)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
    }
    if (ans >= 1e9)
        puts("-1");
    else
        printf("%d", ans);
    return 0;
}