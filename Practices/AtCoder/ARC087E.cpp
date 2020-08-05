// ARC087E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

typedef long long ll;

int n, ptot, ch[MAX_N][2];
ll L;
char S[MAX_N];

inline ll lowbit(ll x) { return x & (-x); }

ll dfs(int u, int dep)
{
    if (u == 0)
        return lowbit(L - dep + 1);
    return dfs(ch[u][0], dep + 1) ^ dfs(ch[u][1], dep + 1);
}

int main()
{
    scanf("%d%lld", &n, &L), ptot = 1;
    for (int i = 1; i <= n; i++)
    {
        scanf("%s", S + 1);
        int p = 1;
        for (int j = 1; S[j]; j++)
        {
            if (ch[p][S[j] - '0'] == 0)
                ch[p][S[j] - '0'] = ++ptot;
            p = ch[p][S[j] - '0'];
        }
    }
    if (dfs(1, 0) == 0)
        puts("Bob");
    else
        puts("Alice");
    return 0;
}