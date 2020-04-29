// P4443.cpp
#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;
typedef long long ll;

const int MAX_N = (1 << 20) + 200;

int n, pi[MAX_N], pos[MAX_N], hval[2][MAX_N], limit;
map<pii, int> mp[4];

int main()
{
    scanf("%d", &n), n = (1 << n), limit = n - 1;
    if (n == 2)
        puts("2"), exit(0);
    for (int i = 1; i <= n; i++)
        scanf("%d", &pi[i]), pos[pi[i]] = i;
    for (int i = 1; i <= n; i++)
    {
        hval[0][i] = hval[0][pos[pi[i] ^ limit]] = rand() | rand() << 15;
        hval[1][i] = hval[1][pos[pi[i] ^ limit]] = rand() | rand() << 15;
    }
    for (int i = 1; i <= n; i++)
        hval[0][i] ^= hval[0][i - 1], hval[1][i] ^= hval[1][i - 1];
    ll ans = 1LL * n * (n + 1) >> 1;
    mp[0][make_pair(0, 0)] = 1;
    for (int i = 1; i <= n; i++)
    {
        int sign = i % 4;
        ans -= mp[sign][make_pair(hval[0][i], hval[1][i])];
        mp[sign][make_pair(hval[0][i], hval[1][i])]++;
    }
    printf("%lld\n", ans);
    return 0;
}