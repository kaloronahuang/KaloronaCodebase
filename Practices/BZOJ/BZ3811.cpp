// BZ3811.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

typedef unsigned long long ll;

int n, idx;
ll ai[MAX_N], g[100];

void solve1()
{
    ll res = 0;
    for (int i = 1; i <= n; i++)
        res |= ai[i];
    printf("%llu", res >> 1);
    if (res & 1)
        puts(".5");
    else
        puts("");
}

void solve2()
{
    ll ans = 0, p4 = 0, res = 0;
    for (int i = 1; i <= n; i++)
        res |= ai[i];
    for (int i = 32; i >= 0; i--)
        for (int j = 32; j >= 0; j--)
        {
            // 2^{i + j};
            if (!(res & (1LL << i)) || !(res & (1LL << j)))
                continue;
            bool flag = false;
            for (int ptr = 1; ptr <= n && !flag; ptr++)
                if ((ai[ptr] >> i & 1) != (ai[ptr] >> j & 1))
                    flag = true;
            if (i + j - 1 - flag < 0)
                ans++;
            else
                p4 += 1LL << (i + j - 1 - flag);
        }
    printf("%llu", (ans >> 1) + p4);
    if (ans & 1)
        puts(".5");
    else
        puts("");
}

void solve3()
{
    int cnt = 0;
    vector<int> buck;
    for (int i = 1; i <= n; i++)
        for (int j = 30; j >= 0; j--)
            if (ai[i] & (1 << j))
            {
                if (g[j])
                    ai[i] ^= g[j];
                else
                {
                    g[j] = ai[i], cnt++, buck.push_back(g[j]);
                    break;
                }
            }
    ll ans = 0, p2 = 0;
    for (int stat = 0; stat < (1 << cnt); stat++)
    {
        int current_val = 0;
        for (int i = 0; i < cnt; i++)
            if (stat & (1 << i))
                current_val ^= buck[i];
        ll a = 0, b = 1;
        for (int i = 1; i <= idx; i++)
        {
            a *= current_val, b *= current_val;
            a += b >> cnt, b &= (1 << cnt) - 1;
        }
        ans += a, p2 += b;
        ans += p2 >> cnt, p2 &= (1 << cnt) - 1;
    }
    printf("%llu", ans);
    if (p2)
        puts(".5");
    else
        puts("");
}

int main()
{
    scanf("%d%d", &n, &idx);
    for (int i = 1; i <= n; i++)
        scanf("%llu", &ai[i]);
    if (idx == 1)
        solve1();
    else if (idx == 2)
        solve2();
    else
        solve3();
    return 0;
}