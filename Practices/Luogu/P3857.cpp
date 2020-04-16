// P3857.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 55, mod = 2008;

typedef long long ll;

int n, m, cnt;
ll g[MAX_N], ai[MAX_N];
char str[MAX_N];

void insert(ll x)
{
    for (int i = n; i >= 0; i--)
        if (x & (1LL << i))
        {
            if (g[i])
                x ^= g[i];
            else
            {
                g[i] = x, cnt++;
                break;
            }
        }
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%s", str);
        ll stat = 0;
        for (int j = 0; j < n; j++)
            stat |= ll(str[j] == 'O') << j;
        insert(stat);
    }
    int ans = 1;
    for (int i = 1; i <= cnt; i++)
        ans = 2LL * ans % mod;
    printf("%d\n", ans);
    return 0;
}