// D.cpp
#include <bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAX_N = 1e5 + 200;
const ll UPPER = 1e10, bitnum = 673;

unordered_map<ull, int> ump;
int n, k, ai[MAX_N], primes[MAX_N], tot, rg, one_siz, idx[MAX_N];
ull pownum[MAX_N];
bool vis[MAX_N];

int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]), rg = max(rg, ai[i]);
    for (int i = 2; i <= rg; i++)
    {
        if (!vis[i])
            primes[++tot] = i, idx[i] = tot;
        for (int j = 1; j <= tot && 1LL * primes[j] * i <= rg; j++)
        {
            vis[i * primes[j]] = true;
            if (i % primes[j] == 0)
                break;
        }
    }
    for (int i = pownum[0] = 1; i <= tot; i++)
        pownum[i] = pownum[i - 1] * bitnum;
    ll ans = 0;
    for (int i = 1; i <= n; i++)
    {
        ull vec = 0, rev = 0;
        int tmp = ai[i], last_idx = 0;
        for (int j = 2; 1LL * j * j <= tmp; j++)
            if (tmp % j == 0)
            {
                int cnt = 0;
                while (tmp % j == 0)
                    tmp /= j, cnt++;
                vec = vec * pownum[idx[j] - last_idx] + cnt % k;
                rev = rev * pownum[idx[j] - last_idx] + ((k - (cnt % k)) % k);
                last_idx = idx[j];
            }
        if (tmp != 1)
        {
            vec = vec * pownum[idx[tmp] - last_idx] + 1 % k;
            rev = rev * pownum[idx[tmp] - last_idx] + ((k - 1) % k);
            last_idx = idx[tmp];
        }
        vec = vec * pownum[tot - last_idx], rev = rev * pownum[tot - last_idx];
        //cout << vec << " " << rev << endl;
        ans += ump[rev], ump[vec]++;
    }
    printf("%lld", ans);
    return 0;
}