// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e7 + 200;

int f[MAX_N], tot, prime[MAX_N], T, l, r;
bool vis[MAX_N];

int main()
{
    scanf("%d", &T);
    for (int i = 2; i < MAX_N; i++)
    {
        if (!vis[i])
            prime[++tot] = i, f[i] = 1;
        for (int j = 1; j <= tot && 1LL * i * prime[j] < MAX_N; j++)
        {
            vis[i * prime[j]] = true;
            if (!vis[i])
                f[i * prime[j]] = 1;
            if (i % prime[j] == 0)
                break;
        }
    }
    for (int i = 1; i < MAX_N; i++)
        f[i] += f[i - 1];
    while (T--)
        scanf("%d%d", &l, &r), printf("%d\n", f[r] - f[l - 1]);
    return 0;
}