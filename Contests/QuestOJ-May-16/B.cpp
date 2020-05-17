// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e5 + 200, bitnum = 13131;

typedef unsigned long long ull;

int n, q, primes[MAX_N], nxt[MAX_N], tot;
bool vis[MAX_N];
char str[MAX_N];
ull pre[MAX_N], pw[MAX_N];

ull getHash(int l, int r) { return pre[r] - pre[l - 1] * pw[r - l + 1]; }

int main()
{
    scanf("%d%s", &n, str + 1);
    for (int i = pw[0] = 1; i <= n; i++)
        pw[i] = 1LL * pw[i - 1] * bitnum;
    for (int i = 1; i <= n; i++)
        pre[i] = pre[i - 1] * bitnum + str[i] - 'a' + 1;
    for (int i = 2; i <= n; i++)
    {
        if (!vis[i])
            primes[++tot] = i, nxt[i] = i;
        for (int j = 1; j <= tot && 1LL * i * primes[j] <= n; j++)
        {
            vis[i * primes[j]] = true;
            nxt[i * primes[j]] = primes[j];
            if (i % primes[j] == 0)
                break;
        }
    }
    scanf("%d", &q);
    while (q--)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        int acc = r - l + 1, len = acc;
        vector<int> c;
        while (acc != 1)
            c.push_back(nxt[acc]), acc /= nxt[acc];
        for (int u : c)
        {
            int clen = len / u;
            if (getHash(l, r - clen) == getHash(l + clen, r))
                len = clen;
        }
        printf("%d\n", len);
    }
    return 0;
}