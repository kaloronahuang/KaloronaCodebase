// CF1150C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 4e5 + 200;

int n, cnt[3], tot, prime[MAX_N], seq[MAX_N];
bool vis[MAX_N];

int main()
{
    scanf("%d", &n);
    for (int i = 1, tmp; i <= n; i++)
        scanf("%d", &tmp), cnt[tmp]++;
    for (int i = 2; i < MAX_N; i++)
    {
        if (!vis[i])
            prime[++tot] = i;
        for (int j = 1; j <= tot && 1LL * i * prime[j] < MAX_N; j++)
        {
            vis[i * prime[j]] = true;
            if (i % prime[j] == 0)
                break;
        }
    }
    int prefix = 0, ans = 0;
    for (int cur = 1, i = 1; cur <= tot && i <= n; cur++)
    {
        while (cnt[2] > 0 && prime[cur] >= prefix + 2 && i <= n)
            prefix += 2, seq[i++] = 2, cnt[2]--;
        while (cnt[1] > 0 && prime[cur] >= prefix + 1 && i <= n)
            prefix += 1, seq[i++] = 1, cnt[1]--;
        if (prefix == prime[cur])
        {
            ans++;
            continue;
        }
    }
    for (int i = 1; i <= n; i++)
        printf("%d ", seq[i]);
    return 0;
}