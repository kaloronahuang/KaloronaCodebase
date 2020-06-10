// P3322.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5050;

typedef long long ll;

int n, ai[MAX_N];
ll fac[MAX_N], ans;

bool check(int st, int idx)
{
    for (int i = 1; i < (1 << idx); i++)
        if (ai[st + i] != ai[st + i - 1] + 1)
            return false;
    return true;
}

void sswap(int s1, int s2, int idx)
{
    for (int i = 0; i < (1 << idx); i++)
        swap(ai[s1 + i], ai[s2 + i]);
}

void dfs(int u, int dep)
{
    if (u > n)
        return (void)(ans += fac[dep]);
    int p1 = 0, p2 = 0;
    for (int i = 1; i <= (1 << n) && p2 == 0; i += (1 << u))
        if (!check(i, u))
            (p1 == 0 ? p1 : p2) = i;
    if (p1 == 0 && p2 == 0)
        dfs(u + 1, dep);
    else if (p2 == 0)
    {
        sswap(p1, p1 + (1 << (u - 1)), u - 1);
        if (check(p1, u))
            dfs(u + 1, dep + 1);
        sswap(p1, p1 + (1 << (u - 1)), u - 1);
    }
    else
    {
        for (int x = 0; x < 2; x++)
            for (int y = 0; y < 2; y++)
            {
                sswap(p1 + x * (1 << (u - 1)), p2 + y * (1 << (u - 1)), u - 1);
                if (check(p1, u) && check(p2, u))
                {
                    dfs(u + 1, dep + 1);
                    sswap(p1 + x * (1 << (u - 1)), p2 + y * (1 << (u - 1)), u - 1);
                    break;
                }
                sswap(p1 + x * (1 << (u - 1)), p2 + y * (1 << (u - 1)), u - 1);
            }
    }
}

int main()
{
    scanf("%d", &n);
    for (int i = fac[0] = 1; i <= 12; i++)
        fac[i] = 1LL * fac[i - 1] * i;
    for (int i = 1; i <= (1 << n); i++)
        scanf("%d", &ai[i]);
    dfs(0, 0), printf("%lld\n", ans);
    return 0;
}