// CF1366D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e5 + 200, MAX_R = 1e7 + 20;

int n, ai[MAX_N], primes[MAX_R], tot;
bool vis[MAX_R];
vector<int> pfactors[MAX_R];

void sieve()
{
    for (int i = 2; i < MAX_R; i++)
    {
        if (!vis[i])
            primes[++tot] = i;
        for (int j = 1; j <= tot && 1LL * i * primes[j] < MAX_R; j++)
        {
            vis[i * primes[j]] = true;
            if (i % primes[j] == 0)
                break;
        }
    }
}

void factorize(int x)
{
    int idx = x;
    for (int i = 1; i <= tot && 1LL * primes[i] * primes[i] <= x; i++)
        if (x % primes[i] == 0)
        {
            pfactors[idx].push_back(primes[i]);
            while (x % primes[i] == 0)
                x /= primes[i];
        }
    if (x > 1)
        pfactors[idx].push_back(x);
}

int main()
{
    scanf("%d", &n), sieve();
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    vector<int> ansBox[2];
    for (int i = 1; i <= n; i++)
    {
        if (!vis[ai[i]])
        {
            ansBox[0].push_back(-1), ansBox[1].push_back(-1);
            continue;
        }
        if (pfactors[ai[i]].empty())
            factorize(ai[i]);
        else if (pfactors[ai[i]].size() == 1)
        {
            ansBox[0].push_back(-1), ansBox[1].push_back(-1);
            continue;
        }
        int x = 1, y = ai[i];
        while (y % pfactors[ai[i]][0] == 0)
            y /= pfactors[ai[i]][0], x *= pfactors[ai[i]][0];
        if (y > 1 && x > 1)
            ansBox[0].push_back(x), ansBox[1].push_back(y);
        else
            ansBox[0].push_back(-1), ansBox[1].push_back(-1);
    }
    for (int x : ansBox[0])
        printf("%d ", x);
    puts("");
    for (int x : ansBox[1])
        printf("%d ", x);
    puts("");
    return 0;
}