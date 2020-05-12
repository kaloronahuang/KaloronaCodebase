// P3538.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e5 + 200, base = 13131;

typedef unsigned long long ull;

int n, q, primes[MAX_N], nxt[MAX_N], tot;
ull pw[MAX_N], pre[MAX_N];
char str[MAX_N];
bool vis[MAX_N];

ull getHash(int l, int r) { return pre[r] - pre[l - 1] * pw[r - l + 1]; }

int main()
{
    scanf("%d%s%d", &n, str + 1, &q);
    for (int i = pw[0] = 1; i <= n; i++)
        pre[i] = pre[i - 1] * base + str[i] - 'a' + 1, pw[i] = pw[i - 1] * base;
    for (int i = 2; i <= n; i++)
    {
        if (!vis[i])
            primes[++tot] = i, nxt[i] = i;
        for (int j = 1; j <= tot && 1LL * i * primes[j] <= n; j++)
        {
            vis[i * primes[j]] = true, nxt[i * primes[j]] = primes[j];
            if (i % primes[j] == 0)
                break;
        }
    }
    while (q--)
    {
        int l, r, len, acc;
        scanf("%d%d", &l, &r), len = acc = r - l + 1;
        vector<int> vec;
        while (acc != 1)
            vec.push_back(nxt[acc]), acc = acc / nxt[acc];
        for (int t : vec)
        {
            int unit = len / t;
            if (getHash(l, r - unit) == getHash(l + unit, r))
                len = unit;
        }
        printf("%d\n", len);
    }
    return 0;
}