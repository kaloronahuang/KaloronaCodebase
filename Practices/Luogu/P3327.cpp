// P3327.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 50100;
int n, prime[MAX_N], tot, mu[MAX_N];
bool vis[MAX_N];
int main()
{
    scanf("%d", &n);
    mu[1] = 1;
    for (int i = 2; i < MAX_N; i++)
    {
        if (!vis[i])
            prime[++tot] = i, mu[i] = -1;
        for (int j = 1; j <= tot && i * prime[j] < MAX_N; j++)
        {
            vis[i * prime[j]] = true;
            if (i % prime[j] == 0)
                break;
            else
                mu[i * prime[j]] = -mu[i];
        }
    }
    
    return 0;
}