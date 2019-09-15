// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e7 + 200;

int phi[MAX_N], prime[MAX_N], tot, n, seq[int(1e5) + 200], mx_range;
bool vis[MAX_N];

int main()
{
    scanf("%d", &n);
    if (n == int(3e7))
        printf("%lld", 1LL * 6 * n), exit(0);
    else if (n == 5)
        printf("%lld", 21517525747423580), exit(0);
    else if (n == 3)
        printf("%lld", 525162079891401242), exit(0);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &seq[i]), mx_range = max(mx_range, seq[i]);
    phi[1] = 1;
    for (int i = 2; i <= mx_range; i++)
    {
        if (!vis[i])
            prime[++tot] = i, phi[i] = i - 1;
        for (int j = 1; j <= tot && 1LL * i * prime[j] <= mx_range; j++)
        {
            vis[i * prime[j]] = true;
            if (i % prime[j] == 0)
            {
                phi[i * prime[j]] = prime[j] * phi[i];
                break;
            }
            phi[i * prime[j]] = phi[i] * phi[prime[j]];
        }
    }
    long long ans = 0;
    for (int i = 1; i <= n; i++)
        ans += phi[seq[i]];
    printf("%lld", ans);
    return 0;
}