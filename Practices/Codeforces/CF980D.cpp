// CF980D.cpp
#pragma GCC optimize(2)
#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;

const int MAX_N = 5050, RANGE = 1e6 + 2000;

int n, ai[MAX_N], ansBox[MAX_N], ptot, bucket[MAX_N];
ull hash_val[MAX_N], bin[RANGE];
unordered_map<int, int> primes;
vector<int> mp;

int main()
{
    scanf("%d", &n);
    for (int i = bin[0] = 1; i < RANGE; i++)
        bin[i] = 133LL * bin[i - 1];
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &ai[i]);
        int acc = ai[i];
        if (acc < 0)
            hash_val[i] = bin[0], acc = -acc;
        for (int j = 2; 1LL * j * j <= acc; j++)
            if (acc % j == 0)
            {
                int parity = 0;
                while (acc % j == 0)
                    acc /= j, parity ^= 1;
                if (parity)
                {
                    if (primes.count(j) == 0)
                        primes[j] = ++ptot;
                    hash_val[i] = hash_val[i] + parity * bin[primes[j]];
                }
            }
        if (acc > 1)
        {
            if (primes.count(acc) == 0)
                primes[acc] = ++ptot;
            hash_val[i] = hash_val[i] + bin[primes[acc]];
        }
    }
    for (int i = 1; i <= n; i++)
        mp.push_back(hash_val[i]);
    sort(mp.begin(), mp.end()), mp.erase(unique(mp.begin(), mp.end()), mp.end());
    for (int i = 1; i <= n; i++)
        hash_val[i] = lower_bound(mp.begin(), mp.end(), hash_val[i]) - mp.begin() + 1;
    for (int i = 1; i <= n; i++)
    {
        int siz = 0;
        for (int j = i; j <= n; j++)
            bucket[hash_val[j]]++, siz += bucket[hash_val[j]] == 1, ansBox[siz]++;
        for (int j = i; j <= n; j++)
            bucket[hash_val[j]]--;
    }
    for (int i = 1; i <= n; i++)
        printf("%d ", ansBox[i]);
    puts("");
    return 0;
}