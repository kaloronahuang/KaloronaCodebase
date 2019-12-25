// 51Nod1190.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 1e5 + 200, mod = 1e9 + 7;

int prime[MAX_N], tot, q, A, B, seqB[MAX_N], idxB[MAX_N], blen, db[MAX_N], dtot;
bool vis[MAX_N];

int quick_pow(int bas, int tim)
{
    int ret = 1;
    while (tim)
    {
        if (tim & 1)
            ret = 1LL * ret * bas % mod;
        bas = 1LL * bas * bas % mod;
        tim >>= 1;
    }
    return ret;
}

const int inv2 = quick_pow(2, mod - 2);

int calc(int a, int b) { return 1LL * (a + b) % mod * ((0LL + b + mod - a + 1) % mod) % mod * inv2 % mod; }

void sieve()
{
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
}

void dfs(int pos, int acc)
{
    if (pos == blen + 1)
        return (void)(db[++dtot] = acc);
    dfs(pos + 1, acc);
    for (int i = 1; i <= idxB[pos]; i++)
        dfs(pos + 1, acc *= seqB[pos]);
}

void factorize(int n)
{
    blen = 0;
    for (int i = 1; i <= tot && 1LL * prime[i] * prime[i] <= n; i++)
        if (n % prime[i] == 0)
        {
            seqB[++blen] = prime[i], idxB[blen] = 0;
            while (n % prime[i] == 0)
                idxB[blen]++, n /= prime[i];
        }
    if (n > 1)
        seqB[++blen] = n, idxB[blen] = 1;
    dtot = 0, dfs(1, 1);
}

int main()
{
    sieve();
    scanf("%d", &q);
    while (q--)
    {
        scanf("%d%d", &A, &B), factorize(B);
        int ans = 0;
        for (int i = 1; i <= dtot; i++)
        {
            int tmp = calc((A + db[i] - 1) / db[i], B / db[i]), acc = 1;
            for (int j = 1; j <= blen; j++)
                if (db[i] % seqB[j] == 0)
                    acc = 1LL * acc * (1 - seqB[j] + mod) % mod;
            ans = (1LL * ans + 1LL * acc * tmp % mod) % mod;
        }
        printf("%lld\n", 1LL * ans * B % mod);
    }
    return 0;
}