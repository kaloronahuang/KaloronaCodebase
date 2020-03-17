// CF1034A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e5 + 200, MAX_P = 1.5e7 + 200;

int n, ai[MAX_N], primes[MAX_P], ptot, gloabl_gcd, cnt[MAX_P], sfactor[MAX_P];
bool vis[MAX_P];

int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

int main()
{
    // sieve process;
    for (int i = 2; i < MAX_P; i++)
    {
        if (!vis[i])
            primes[++ptot] = i;
        for (int j = 1; j <= ptot && 1LL * primes[j] * i < MAX_P; j++)
        {
            vis[i * primes[j]] = true;
            if (i % primes[j] == 0)
                break;
        }
    }
    for (int i = 2; i < MAX_P; i++)
        sfactor[i] = i;
    for (int i = 2; i < MAX_P; i++)
        if (!vis[i])
            for (int j = (i << 1); j < MAX_P; j += i)
                if (sfactor[j] == j)
                    sfactor[j] = i;
    // read;
    scanf("%d%d", &n, &gloabl_gcd), ai[1] = gloabl_gcd;
    for (int i = 2; i <= n; i++)
        scanf("%d", &ai[i]), gloabl_gcd = gcd(gloabl_gcd, ai[i]);
    for (int i = 1; i <= n; i++)
        ai[i] /= gloabl_gcd;
    for (int i = 1; i <= n; i++)
    {
        int curt = ai[i];
        while (curt != 1)
        {
            int x = sfactor[curt];
            cnt[x]++;
            while (sfactor[curt] == x)
                curt /= sfactor[curt];
        }
    }
    int ans = n;
    for (int i = 1; i < MAX_P; i++)
        ans = min(ans, n - cnt[i]);
    if (ans == n)
        puts("-1");
    else
        printf("%d\n", ans);
    return 0;
}