// P3532.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

int n, ai[MAX_N], id[MAX_N], fac[MAX_N], ans[MAX_N], ansId[MAX_N], primes[MAX_N], tot, nxt[MAX_N];
bool vis[MAX_N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]), nxt[i] = id[ai[i]], id[ai[i]] = i, ans[i] = 2e9;
    for (int i = 2; i < MAX_N; i++)
    {
        if (!vis[i])
            primes[++tot] = i, fac[i] = 1;
        for (int j = 1; j <= tot && 1LL * i * primes[j] < MAX_N; j++)
        {
            fac[i * primes[j]] = fac[i] + 1, vis[i * primes[j]] = true;
            if (i % primes[j] == 0)
                break;
        }
    }
    for (int d = 1; d < MAX_N; d++)
    {
        vector<int> vec;
        for (int u = d; u < MAX_N; u += d)
            for (int i = id[u]; i; i = nxt[i])
                vec.push_back(i);
        if (vec.empty())
            continue;
        int key = vec.front();
        for (int i = 1, siz = vec.size(); i < siz; i++)
            if (fac[ai[vec[i]]] < fac[ai[key]] || (fac[ai[vec[i]]] == fac[ai[key]] && vec[i] < key))
                swap(key, vec[i]);
        for (int i = 1, siz = vec.size(); i < siz; i++)
        {
            int u = vec[i], g = fac[ai[u]] + fac[ai[key]] - (fac[d] << 1);
            if (g < ans[u] || (g == ans[u] && key < ansId[u]))
                ans[u] = g, ansId[u] = key;
            if (g < ans[key] || (g == ans[key] && u < ansId[key]))
                ans[key] = g, ansId[key] = u;
        }
    }
    for (int i = 1; i <= n; i++)
        printf("%d\n", ansId[i]);
    return 0;
}